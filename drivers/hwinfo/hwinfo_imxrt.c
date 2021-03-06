/*
 * Copyright (c) 2019 Alexander Wachter
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <soc.h>
#include <drivers/hwinfo.h>
#include <string.h>
#include <sys/byteorder.h>

struct imxrt_uid {
	u32_t id[2];
};

ssize_t z_impl_hwinfo_get_device_id(u8_t *buffer, size_t length)
{
	struct imxrt_uid dev_id;

	dev_id.id[0] = sys_cpu_to_be32(OCOTP->CFG2);
	dev_id.id[1] = sys_cpu_to_be32(OCOTP->CFG1);

	if (length > sizeof(dev_id.id)) {
		length = sizeof(dev_id.id);
	}

	memcpy(buffer, dev_id.id, length);

	return length;
}
