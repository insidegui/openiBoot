#include "nand.h"
#include "util.h"

void nand_device_init(nand_device_t *_nand)
{
	memset(_nand, 0, sizeof(*_nand));

	device_init(&_nand->device);
	_nand->device.fourcc = FOURCC('N', 'A', 'N', 'D');

	device_register(&_nand->device);
}

void nand_device_cleanup(nand_device_t *_nand)
{
}

nand_device_t *nand_device_allocate()
{
	nand_device_t *ret = malloc(sizeof(*ret));
	nand_device_init(ret);
	return ret;
}

error_t nand_device_read_single_page(nand_device_t *_dev, uint32_t _chip, uint32_t _block,
		uint32_t _page, uint8_t *_buffer, uint8_t *_spareBuffer)
{
	if(!_dev->read_single_page)
		return ENOENT;

	return _dev->read_single_page(_dev, _chip, _block, _page, _buffer, _spareBuffer);
}

error_t nand_device_write_single_page(nand_device_t *_dev, uint32_t _chip, uint32_t _block,
		uint32_t _page, uint8_t *_buffer, uint8_t *_spareBuffer)
{
	if(!_dev->write_single_page)
		return ENOENT;

	return _dev->write_single_page(_dev, _chip, _block, _page, _buffer, _spareBuffer);
}

error_t nand_device_read_special_page(nand_device_t *_dev, uint32_t _ce, char _page[16], uint8_t *_buffer, size_t _amt)
{
	uint32_t bytesPerPage, blocksPerCE, pagesPerBlock;

	error_t ret = nand_device_get_info(_dev, diBytesPerPage, &bytesPerPage, sizeof(bytesPerPage));
	if(FAILED(ret))
		return EINVAL;

	ret = nand_device_get_info(_dev, diBlocksPerCE, &blocksPerCE, sizeof(blocksPerCE));
	if(FAILED(ret))
		return EINVAL;

	ret = nand_device_get_info(_dev, diPagesPerBlock, &pagesPerBlock, sizeof(pagesPerBlock));
	if(FAILED(ret))
		return EINVAL;

	uint8_t* buffer = malloc(bytesPerPage);
	int lowestBlock = blocksPerCE - (blocksPerCE / 10);
	int block;
	for(block = blocksPerCE - 1; block >= lowestBlock; block--)
	{
		int page;
		int badBlockCount = 0;
		for(page = 0; page < pagesPerBlock; page++)
		{
			if(badBlockCount > 2)
			{
				DebugPrintf("vfl: read_special_page - too many bad pages, skipping block %d\r\n", block);
				break;
			}

			int ret = nand_device_read_single_page(_dev, _ce, block, page, buffer, NULL);
			if(ret != 0)
			{
				if(ret == 1)
				{
					DebugPrintf("vfl: read_special_page - found 'badBlock' on ce %d, page %d\r\n", (block * pagesPerBlock) + page);
					badBlockCount++;
				}

				DebugPrintf("vfl: read_special_page - skipping ce %d, page %d\r\n", (block * pagesPerBlock) + page);
				continue;
			}

			if(memcmp(buffer, _page, sizeof(_page)) == 0)
			{
				if(_buffer)
				{
					size_t amt = ((size_t*)buffer)[13]; 
					if(amt > _amt)
						amt = _amt;

					memcpy(_buffer, buffer + 0x38, amt);
				}

				free(buffer);
				return SUCCESS;
			}
			else
				DebugPrintf("vfl: did not find signature on ce %d, page %d\r\n", (block * pagesPerBlock) + page);
		}
	}

	free(buffer);
	return ENOENT;
}

void nand_device_enable_encryption(nand_device_t *_dev, int _enabled)
{
	if(_dev->enable_encryption)
		_dev->enable_encryption(_dev, _enabled);
}

