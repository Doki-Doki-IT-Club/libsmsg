# Intro

`SMSG` is a library designed for convenient interaction between client and server applications. Convenience is provided by providing APIs for various programming languages that use absolutely identical data structures (including in terms of memory) and methods of interacting with this data.

The library is written in C. At the moment, JNI support is implemented.

# Functional Requirements

## REQ010

The library should implement the following types of `SMSG` messages:

+ Header of message  (`sm`)
+ Service message (`sm_service`)
+ User message (`sm_message`)
+ Initialization information (`sm_client_init`)
+ List of online users (`sm_users_online`)

## REQ020

The library should implement the following methods of interacting with SMSG objects:

+ `sm_create` - Create new SMSG object with needed type.
+ `sm_destroy` - Destroy the SMSG object.
+ `sm_get_size` - Return size of current SMSG object.
+ `sm_get_type` - Return type of current SMSG object.
+ `sm_get_value` - Return pointer to value in current SMSG object.
+ `sm_size_by_type` - Set `super.size` with current SMSG type
+ `sm_set_value` - Set new value to current field in current SMSG object.
+ `sm_parse_field_num` - Return number of field by string name in current SMSG object.

as well as the following service methods that do not interact with objects directly:

+ `sm_parse_type_num` - Return number of type by string name in current SMSG object.
+ `intTP` - Return pointer to int value.
+ `intPT` - Return int value by pointer.
+ `smStringPT` (only for JNI) - Return String value by pointer.

## REQ030

The struct of each `SMSG` object must begin with the Header (`sm`) and provide access to its fields.

## REQ040

`sm_create` method shall:

- Return a pointer to a heap-allocated struct of a given type.
- Fill all allocated memory with zeros.
- Set `super.type` in given type.
- In case of `malloc` error return `NULL`.
- In case of entering a non-existent type, return `NULL`.

## REQ050

`sm_destroy` method shall:

- Free all allocated memory by given pointer
- Do nothing if pointer is `NULL`;
- Set pointer to `NULL` after free.

## REQ060

`sm_get_size` method shall:

- Return `super.size` in struct by given pointer.
- Return error with code ` -1` if given pointer is `NULL`.

## REQ070

`sm_get_type` method shall:

- Return `super.type` in struct by given pointer.
- Return error with code ` -1` if given pointer is `NULL`.

## REQ080

`sm_get_value` method shall:

- Return pointer to value at given position is struct by given pointer.
- In case of entering a non-existent `position` return `NULL`;
- Return `NULL` if given pointer is `NULL`.

## REQ090

`sm_size_by_type` method shall:

- Return struct data size by given `SMSG` object pointer .
- In case of `super.type` is invalid return ` -1`.
- Return `NULL` if given pointer is `NULL`.

## REQ100

`sm_set_value` method shall:

- Set value at given position is struct by given pointer.
- In case of entering a non-existent `position` return `NULL`;
- Return `NULL` if given pointer is `NULL`.

## REQ110

`sm_parse_field_num` method shall:

- Return field number by string name in `SMSG` object by given pointer.
- In case of entering a non-existent field name return ` -1`.
- Return ` -1` if given pointer is `NULL`.

## REQ120

`sm_parse_type_num` method shall:

- Return `SMSG` object type by string name.
- In case of entering a non-existent type name return ` -1`;

## REQ130

`intTP` method shall:

- Return pointer to a heap-allocated interger value by given integer.
- In case of `malloc` error return `NULL`.

## REQ140

`intPT` method shall:

- Return integer by given pointer to value.
- In case of pointer is `NULL` return `0`.

## REQ150

`smStringPT` method shall:

- Return String (up to 1024 chars) by given pointer to start of char array.

## REQ160

Users-online-list should provide the ability to store names of up to 64 users.