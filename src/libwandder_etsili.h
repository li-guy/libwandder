/*
 *
 * Copyright (c) 2017-2019 The University of Waikato, Hamilton, New Zealand.
 * All rights reserved.
 *
 * This file is part of libwandder.
 *
 * This code has been developed by the University of Waikato WAND
 * research group. For further information please see http://www.wand.net.nz/
 *
 * libwandder is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * libwandder is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Shane Alcock
 */

#ifndef LIBWANDDER_ETSILI_H_
#define LIBWANDDER_ETSILI_H_

#include <libwandder.h>
#include <stdint.h>

#define WANDDER_ETSILI_PSDOMAINID (etsi_lipsdomainid)

#define MEMCPYPREENCODE(ptr, itembuf) {memcpy(ptr, itembuf->buf, itembuf->len); ptr+=itembuf->len;}

#define ENDCONSTRUCTEDBLOCK(ptr,num) memset(ptr, 0, num*2);ptr+=num*2;

extern const uint8_t etsi_lipsdomainid[9];

typedef struct wandder_etsistack {

    int alloced;
    int current;
    wandder_dumper_t **stk;
    int *atthislevel;
} wandder_etsi_stack_t;

typedef struct wandder_etsispec {
    wandder_dumper_t ipaddress;
    wandder_dumper_t datanodeaddress;
    wandder_dumper_t timestamp;
    wandder_dumper_t localtimestamp;
    wandder_dumper_t ipvalue;
    wandder_dumper_t nationalipmmiri;
    wandder_dumper_t h323content;
    wandder_dumper_t h323message;
    wandder_dumper_t sipmessage;
    wandder_dumper_t ipmmiricontents;
    wandder_dumper_t ipmmiri;
    wandder_dumper_t ipiriid;
    wandder_dumper_t ipiricontents;
    wandder_dumper_t ipiri;
    wandder_dumper_t umtsiri;
    wandder_dumper_t umtsiri_params;
    wandder_dumper_t iricontents;
    wandder_dumper_t iripayload;
    wandder_dumper_t netelid;
    wandder_dumper_t root;
    wandder_dumper_t linetid;
    wandder_dumper_t networkidentifier;
    wandder_dumper_t location;
    wandder_dumper_t partyinfo;
    wandder_dumper_t partyidentity;
    wandder_dumper_t servicesdatainfo;
    wandder_dumper_t gprsparams;
    wandder_dumper_t cid;
    wandder_dumper_t msts;
    wandder_dumper_t cccontents;
    wandder_dumper_t ccpayloadseq;
    wandder_dumper_t ccpayload;
    wandder_dumper_t operatorleamessage;
    wandder_dumper_t option;
    wandder_dumper_t optionseq;
    wandder_dumper_t optionreq;
    wandder_dumper_t optionresp;
    wandder_dumper_t inclseqnos;
    wandder_dumper_t integritycheck;
    wandder_dumper_t tripayload;
    wandder_dumper_t payload;
    wandder_dumper_t psheader;
    wandder_dumper_t pspdu;
    wandder_dumper_t ipmmcc;
    wandder_dumper_t ipcc;
    wandder_dumper_t ipcccontents;
    wandder_dumper_t iripayloadseq;

    wandder_decoder_t *dec;
    wandder_etsi_stack_t *stack;

    uint8_t decstate;
} wandder_etsispec_t;

typedef enum wandder_body_type {
    WANDDER_ETSILI_EMPTY,
    WANDDER_ETSILI_IPCC,
    WANDDER_ETSILI_IPMMCC,
    WANDDER_ETSILI_IPIRI,
    WANDDER_ETSILI_IPMMIRI,
} wandder_body_type_t;

typedef enum {
    WANDDER_ETSILI_IRI_BEGIN = 1,
    WANDDER_ETSILI_IRI_END = 2,
    WANDDER_ETSILI_IRI_CONTINUE = 3,
    WANDDER_ETSILI_IRI_REPORT = 4
} wandder_etsili_iri_type_t;

typedef struct wandder_pshdr {
    uint8_t* cin;
    uint8_t* seqno;
    uint8_t* sec;
    uint8_t* usec;
    uint8_t* end;
} wandder_pshdr_t;

typedef struct wandder_ipcc_body {
    uint8_t* dir;
    uint8_t* ipcontent;
} wandder_ipcc_body_t;

typedef struct wandder_ipmmcc_body {
    uint8_t* dir;
    uint8_t* ipcontent;
} wandder_ipmmcc_body_t;

typedef struct wandder_ipiri_body {
    uint8_t* iritype;
    uint8_t* params;
} wandder_ipiri_body_t;

typedef struct wandder_ipmmiri_body {
    uint8_t* iritype;
    uint8_t* ipcontent;
} wandder_ipmmiri_body_t;

typedef struct wandder_etsili_top {
    uint8_t* buf;
    size_t len;
    size_t alloc_len;
    wandder_pshdr_t header;
    wandder_body_type_t body_type;
    union {
        wandder_ipcc_body_t ipcc;
        wandder_ipmmcc_body_t ipmmcc;
        wandder_ipmmiri_body_t ipmmiri;
        wandder_ipiri_body_t ipiri;
    } body;
} wandder_etsili_top_t;


typedef enum {
    WANDDER_PREENCODE_USEQUENCE,
    WANDDER_PREENCODE_CSEQUENCE_0,
    WANDDER_PREENCODE_CSEQUENCE_1,
    WANDDER_PREENCODE_CSEQUENCE_2,
    WANDDER_PREENCODE_CSEQUENCE_3,
    WANDDER_PREENCODE_CSEQUENCE_7,	/* Microsecond timestamp */
    WANDDER_PREENCODE_CSEQUENCE_11,  /* IPMMIRI */
    WANDDER_PREENCODE_CSEQUENCE_12,  /* IPMMCC */
    WANDDER_PREENCODE_PSDOMAINID,
    WANDDER_PREENCODE_LIID,
    WANDDER_PREENCODE_AUTHCC,
    WANDDER_PREENCODE_OPERATORID,
    WANDDER_PREENCODE_NETWORKELEMID,
    WANDDER_PREENCODE_DELIVCC,
    WANDDER_PREENCODE_INTPOINTID,
    WANDDER_PREENCODE_TVCLASS,
    WANDDER_PREENCODE_IPMMIRIOID,
    WANDDER_PREENCODE_IPCCOID,
    WANDDER_PREENCODE_IPIRIOID,
    WANDDER_PREENCODE_IPMMCCOID,
    WANDDER_PREENCODE_DIRFROM,
    WANDDER_PREENCODE_DIRTO,
    WANDDER_PREENCODE_DIRUNKNOWN,
    WANDDER_PREENCODE_LIID_LEN,
    WANDDER_PREENCODE_LAST

} wandder_preencode_index_t;

typedef struct wandder_etsili_intercept_details {
    char *liid;
    char *authcc;
    char *delivcc;
    char *intpointid;
    char *operatorid;
    char *networkelemid;
} wandder_etsili_intercept_details_t;

enum {
    WANDDER_IRI_CONTENT_IP,
    WANDDER_IRI_CONTENT_SIP,
};

typedef struct wandder_etsili_ipaddress {
    uint8_t iptype;
    uint8_t assignment;
    uint8_t v6prefixlen;
    uint32_t v4subnetmask;

    uint8_t valtype;
    uint8_t *ipvalue;
} wandder_etsili_ipaddress_t;

enum {
    WANDDER_IPADDRESS_REP_BINARY = 1,
    WANDDER_IPADDRESS_REP_TEXT = 2,
};

enum {
    WANDDER_IPADDRESS_ASSIGNED_STATIC = 1,
    WANDDER_IPADDRESS_ASSIGNED_DYNAMIC = 2,
    WANDDER_IPADDRESS_ASSIGNED_UNKNOWN = 3,
};
enum {
    WANDDER_IPADDRESS_VERSION_4 = 0,
    WANDDER_IPADDRESS_VERSION_6 = 1,
};

wandder_etsispec_t *wandder_create_etsili_decoder(void);
void wandder_free_etsili_decoder(wandder_etsispec_t *dec);
void wandder_attach_etsili_buffer(wandder_etsispec_t *dec, uint8_t *buffer,
        uint32_t len, bool copy);

wandder_dumper_t *wandder_get_etsili_structure(wandder_etsispec_t *dec);

wandder_decoder_t *wandder_get_etsili_base_decoder(wandder_etsispec_t *dec);
struct timeval wandder_etsili_get_header_timestamp(wandder_etsispec_t *dec);
uint32_t wandder_etsili_get_pdu_length(wandder_etsispec_t *dec);
char *wandder_etsili_get_next_fieldstr(wandder_etsispec_t *dec, char *space,
        int spacelen);
uint8_t *wandder_etsili_get_cc_contents(wandder_etsispec_t *dec, uint32_t *len,
        char *name, int namelen);
uint8_t *wandder_etsili_get_iri_contents(wandder_etsispec_t *dec,
        uint32_t *len, uint8_t *ident, char *name, int namelen);
char *wandder_etsili_get_liid(wandder_etsispec_t *dec, char *space,
        int spacelen);
uint32_t wandder_etsili_get_cin(wandder_etsispec_t *dec);
int wandder_etsili_is_keepalive(wandder_etsispec_t *etsidec);
int wandder_etsili_is_keepalive_response(wandder_etsispec_t *etsidec);
int64_t wandder_etsili_get_sequence_number(wandder_etsispec_t *etsidec);



void wandder_init_pshdr_ber(wandder_buf_t **precomputed, wandder_etsili_top_t *top);
void wandder_free_top(wandder_etsili_top_t *top);
void wandder_encode_etsi_ipcc_ber(
        wandder_buf_t **precomputed, int64_t cin, int64_t seqno,
        struct timeval *tv, void *ipcontents, size_t iplen, uint8_t dir,
        wandder_etsili_top_t *top);
void wandder_encode_etsi_ipmmcc_ber(
        wandder_buf_t **precomputed, int64_t cin, int64_t seqno,
        struct timeval *tv, void *ipcontents, size_t iplen, uint8_t dir,
        wandder_etsili_top_t *top);

void wandder_encode_etsi_ipmmiri_ber(
        wandder_buf_t **precomputed, int64_t cin, int64_t seqno,
        struct timeval *tv, void *ipcontents, size_t iplen, wandder_etsili_iri_type_t iritype,
        uint8_t *ipsrc, uint8_t *ipdest, int ipfamily,
        wandder_etsili_top_t *top);

void wandder_encode_etsi_ipiri_ber(
        wandder_buf_t **precomputed, int64_t cin, int64_t seqno,
        struct timeval *tv, void* params, wandder_etsili_iri_type_t iritype,
        wandder_etsili_top_t *top);

void wandder_etsili_preencode_static_fields_ber(
        wandder_buf_t **pendarray, wandder_etsili_intercept_details_t *details);
void wandder_etsili_clear_preencoded_fields_ber(wandder_buf_t **pendarray);



#endif
// vim: set sw=4 tabstop=4 softtabstop=4 expandtab :
