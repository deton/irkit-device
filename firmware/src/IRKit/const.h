/*
 Copyright (C) 2013-2014 Masakazu Ohtsuka
  
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 2 of the License, or
 (at your option) any later version.
  
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
  
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __CONST_H__
#define __CONST_H__

#define SHARED_BUFFER_SIZE 512

#define EEPROM_KEYS_OFFSET                0

// sizeof(KeysShared)
#define EEPROM_INDEPENDENT_OFFSET       200

// sizeof(KeysShared) + sizeof(KeysIndependent)
#define EEPROM_PACKERTREE_OFFSET        235

// sizeof(KeysShared) + sizeof(KeysIndependent) + sizeof(tree)
#define EEPROM_LIMITEDAPPASSWORD_OFFSET 571
// length = 10 characters + NULL
#define EEPROM_LIMITEDAPPASSWORD_LENGTH  11

#endif
