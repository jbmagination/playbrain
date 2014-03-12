/* search.c
 *   by Alex Chadwick
 * 
 * Copyright (C) 2014, Alex Chadwick
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* This file should ideally avoid Wii specific methods so unit testing can be
 * conducted elsewhere. */
 
#include "search.h"
 
static symbol_t *Search_AllocSymbol(const char *name, size_t name_length) {
    symbol_t *symbol;
    
    assert(name);
    
    symbol = malloc(sizeof(symbol_t));
    
    if (symbol != NULL) {
        char *name_alloc;
        
        name_alloc = malloc(name_length + 1);
        
        if (name_alloc != NULL) {
            strncpy(name_alloc, name, name_length);
            symbol->name = name_alloc;
            symbol->relocation = NULL;
        } else {
            free(symbol);
            symbol = NULL;
        }
    }
    
    return symbol;
}

static relocation_instance_t *Search_AllocSymbolRelocation(
        symbol_t *symbol, const symbol_t *target,
        relocation_t type, unsigned int offset) {
    relocation_instance_t *reloc;
    
    assert(symbol);
    
    reloc = malloc(sizeof(relocation_instance_t));
    
    if (reloc != NULL) {
        reloc->type = type;
        reloc->offset = offset;
        reloc->next = symbol->relocation;
        symbol->relocation = reloc;
    }
    
    return reloc;
}