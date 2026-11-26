/* Copyright (c) 2008-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#ifndef MDSS_BOE_HD_DSI_PANEL_H
#define MDSS_BOE_HD_DSI_PANEL_H
#include "mdss_panel.h"
#include "dsi_tcon_mdnie_lite.h"
enum {
	MIPI_RESUME_STATE,
	MIPI_SUSPEND_STATE,
};
 struct display_status{
	unsigned char auto_brightness;
	int bright_level;
	int siop_status;
 };
 struct mdss_samsung_driver_data{
	struct msm_fb_data_type *mfd;
	struct mdss_panel_data *mpd;
	struct platform_device *msm_pdev;
	struct display_status dstat;
	struct mdnie_lite_tun_type *mdnie_tune_state;
	struct completion esd_recovery_done;
	struct work_struct  err_fg_work;
	int err_fg_irq_num;
	int err_fg_gpio;
	int esd_count;


	int pre_bl;

 };
void make_sync_esd(void);
void mdss_dsi_cmds_send(struct mdss_dsi_ctrl_pdata *ctrl, struct dsi_cmd_desc *cmds, int cnt,int flag);
#endif
