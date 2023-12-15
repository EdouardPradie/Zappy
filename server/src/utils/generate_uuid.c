/*
** EPITECH PROJECT, 2023
** utils
** File description:
** generate_uuid
*/

#include <stdlib.h>
#include <uuid/uuid.h>

static const int UUID_SIZE = 36;

char *generate_uuid(void)
{
    char *unparsed = malloc(sizeof(char) * (UUID_SIZE + 1));
    uuid_t uuid = {0};

    if (!unparsed)
        return NULL;
    uuid_generate(uuid);
    uuid_unparse(uuid, unparsed);
    return unparsed;
}
