#include "bits.h"
#include "cache.h"

int get_set(Cache *cache, address_type address) {
  // TODO:
  //  Extract the set bits from a 32-bit address.
  //

  unsigned int u_address = (unsigned int) address;
  u_address = u_address << (32 - (cache->set_bits) - (cache->block_bits));
  u_address = u_address >> (32 - (cache->set_bits));
  
  return u_address;
}

int get_line(Cache *cache, address_type address) {
  // TODO:
  // Extract the tag bits from a 32-bit address.
  //
  unsigned int u_address = (unsigned int) address;
  u_address = u_address >> ((cache->set_bits + cache->block_bits));
  
  return u_address;
}

int get_byte(Cache *cache, address_type address) {
  // TODO
  // Extract the block offset (byte index) bits from a 32-bit address.
  //

  unsigned int u_address = (unsigned int) address;
  u_address = u_address << (32 - (cache->block_bits));
  u_address = u_address >> (32 - (cache->block_bits));
  
  return u_address;
}
