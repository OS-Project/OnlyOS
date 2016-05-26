void mfree_block(MEMORY_BLOCK * block, MEMORY * memory)
{
    unsigned int k;
    MEMORY_MAPPER * mapper = memory->mapper;

    switch (mapper->nb_blocks) {
        case 0:
            break;
        case 1:
            mapper->nb_blocks--;

            MEMORY_BLOCK * block = mapper->blocks[0];

            for (unsigned int i = 0; i < mapper->end_adress; i++) {
                char *byte = (char *)mapper->blocks[mapper->nb_blocks - 1];
                *byte = 0x0;
            }
            break;
        default:
            k = 0;
            while (mapper->blocks[k]->start_adress != block->start_adress && k < mapper->nb_blocks)
                k++;

            if (k != mapper->nb_blocks) {
                /* Copy all blocks */
                for (unsigned int i = 0; i < mapper->nb_blocks - k; k++)
                    mcopy_block(mapper->blocks[i + k], mapper->blocks[i + k + 1]);

                /* Remove the last block (optionnal) */
                for (unsigned int i = 0; i < mapper->end_adress; i++) {
                    char *byte = (char *)mapper->blocks[mapper->nb_blocks - 1];
                    *byte = 0x0;
                }

                mapper->nb_blocks--;
            }
            else
                kexit(2); /* Error */
            break;
    }
}

void mcopy_block(MEMORY_BLOCK * destination_block, MEMORY_BLOCK * source_block)
{
    destination_block->start_adress = source_block->start_adress;
    destination_block->end_adress = source_block->end_adress;
    destination_block->size = source_block->size;
    destination_block->total_size = source_block->total_size;
    destination_block->nb_page = source_block->nb_page;
}