#ifndef __BUFFERS_H_
#define __BUFFERS_H_

#include <stdio.h>
#include <mos_api.h>

/**
 * @brief Clear the buffer with the given ID. If the buffer does not exist then this command will do nothing.
 * 
 * VDU 23, 0 &A0, bufferId; 2
 * 
 * Please note that this clears out all of the blocks sent to a buffer via 
 * command 0, not just the last one. i.e. if you have built up a buffer over 
 * time by sending multiple commands to write to the same buffer ID, this 
 * command will clear out all of those commands.
 * 
 * Calling this command with a bufferId value of -1 (65535) will clear out 
 * all buffers.
 * 
 * @param buffer_id 16 bit Buffer ID
 */
void vdp_clear_buffer(uint16_t buffer_id);

/**
 * @brief Select bitmap using a 16-bit buffer ID
 * 
 * VDU 23, 27, &20, bufferId;
 * 
 * This command is essentially identical to VDU 23, 27, 0, n, 
 * however it uses a 16-bit buffer ID instead of an 8-bit bitmap ID.
 * 
 * @param buffer_id 16 Bit Buffer ID
 */
void vdp_select_buffer(uint16_t buffer_id);

/**
 * @brief Writes data to a buffer
 * 
 * VDU 23, 0 &A0, bufferId; 0, length; <buffer-data>
 * 
 * @param buffer_id 
 * @param buffer_content 
 * @param buffer_size 
 */
void add_stream_to_buffer(uint16_t buffer_id, char *buffer_content, uint16_t buffer_size);
void vdp_extended_select(uint16_t buffer_id);
void vdp_consolidate_buffer(uint16_t buffer_id);
void vdp_split_into_from(uint16_t buffer_id, uint16_t into, uint16_t from);
void vdp_split_into_cols_from(uint16_t buffer_id, uint16_t width, uint16_t cols, uint16_t from);


#endif