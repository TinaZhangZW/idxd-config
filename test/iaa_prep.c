// SPDX-License-Identifier: GPL-2.0
/* Copyright(c) 2019 Intel Corporation. All rights reserved. */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <accfg/idxd.h>
#include "accel_test.h"
#include "iaa.h"

void iaa_prep_noop(struct task *tsk)
{
	info("preparing descriptor for noop\n");

	tsk->dflags = IDXD_OP_FLAG_CRAV | IDXD_OP_FLAG_RCR;
	acctest_prep_desc_common(tsk->desc, tsk->opcode, 0,
				 (uint64_t)(tsk->src1), 0, tsk->dflags);
	tsk->desc->completion_addr = (uint64_t)(tsk->comp);
	tsk->comp->status = 0;
}

void iaa_prep_crc64(struct task *tsk)
{
	info("preparing descriptor for crc64\n");

	acctest_prep_desc_common(tsk->desc, tsk->opcode, 0,
				 (uint64_t)(tsk->src1), tsk->xfer_size, tsk->dflags);
	tsk->desc->completion_addr = (uint64_t)(tsk->comp);
	tsk->desc->iax_crc64_flags = tsk->iaa_crc64_flags;
	tsk->desc->iax_crc64_poly = tsk->iaa_crc64_poly;
	tsk->comp->status = 0;
}

void iaa_prep_zcompress16(struct task *tsk)
{
	info("preparing descriptor for zcompress16\n");

	acctest_prep_desc_common(tsk->desc, tsk->opcode, (uint64_t)(tsk->dst1),
				 (uint64_t)(tsk->src1), tsk->xfer_size, tsk->dflags);
	tsk->desc->completion_addr = (uint64_t)(tsk->comp);
	tsk->desc->iax_max_dst_size = tsk->iaa_max_dst_size;
	tsk->comp->status = 0;
}

void iaa_prep_zdecompress16(struct task *tsk)
{
	info("preparing descriptor for zdecompress16\n");

	acctest_prep_desc_common(tsk->desc, tsk->opcode, (uint64_t)(tsk->dst1),
				 (uint64_t)(tsk->src1), tsk->xfer_size, tsk->dflags);
	tsk->desc->completion_addr = (uint64_t)(tsk->comp);
	tsk->desc->iax_max_dst_size = tsk->iaa_max_dst_size;
	tsk->comp->status = 0;
}

void iaa_prep_zcompress32(struct task *tsk)
{
	info("preparing descriptor for zcompress32\n");

	acctest_prep_desc_common(tsk->desc, tsk->opcode, (uint64_t)(tsk->dst1),
				 (uint64_t)(tsk->src1), tsk->xfer_size, tsk->dflags);
	tsk->desc->completion_addr = (uint64_t)(tsk->comp);
	tsk->desc->iax_max_dst_size = tsk->iaa_max_dst_size;
	tsk->comp->status = 0;
}
