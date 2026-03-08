# Emu68MailBoxExample1

This is a `C89` example that shows how to use the new Emu68 `mailbox.resource`

## Why use the new mailbox.resource

It is a good practical now with Emu68 1.1+ to use the new `mailbox.resource` (https://github.com/michalsc/mailbox.resource), this ensures safer accesses to the rpi `mailbox`, by benefiting of __semaphoring__, native __big-endian__ conversion, __rpi-aligned__ buffer, and more, especially when multiple programs bangs the rpi `mailbox` __simultaneously__, for example, Emu68 drivers + Genet + Emu68Control or Emu68Meter or Emu68EnvCX at same time.

## Requirements

### Emu68 1.1+ from
* https://github.com/michalsc/Emu68/releases
* https://github.com/michalsc/Emu68/releases/download/v1.1.0-alpha.1/Emu68-pistorm.zip

### Emu68-tools for Emu 68 1.1+ from
* https://github.com/michalsc/Emu68-tools/releases
* https://github.com/michalsc/Emu68-tools/releases/download/v1.1/Emu68-tools.zip

## Installation

### Copy the Emu68-tools headers from the archive to your amiga SDK headers
* Emu68-tools\Developer\include ➜ SDK

Nothing more needed, the resource itself is embedded in the Emu68 1.1+ rom

## Usage

### Includes this headers in your program

```c
#include <resources/mailbox.h>
#include <proto/mailbox.h>
```

### Open the resource

⚠️ Do not try to close `MailboxBase`, contrary to a `.library`, a `.resource` doesnt need to be closed on AmigaOS, by design, since it's always available from the rom.

```c
APTR MailboxBase;

if (MailboxBase = OpenResource("mailbox.resource"))
{
    // code start here
}
```

### Use MB_RawCommand() to make a mailbox request

```c
ULONG cmd[8];
cmd[0] = 8 * 4;  // Request size in bytes
cmd[1] = 0;      // Request return code
cmd[2] = tag;    // Request tag identifier
cmd[3] = 2 * 4;  // Response size in bytes
cmd[4] = 0;      // Response code
cmd[5] = arg;    // Response[0]
cmd[6] = 0;      // Response[1]
cmd[7] = 0;      // End of request
MB_RawCommand(cmd);
```

### Use MB_VCGenCmd() to make mailbox linux vcgencmd-style requests

```c
UBYTE result[1024];
result[0] = 0;
MB_VCGenCmd("commands", result, 1024);
PutStr(result);
```

This example outputs the available `vcgencmd` commands :

commands="commands, set_logging, bootloader_config, bootloader_version, cache_flush, codec_enabled, get_mem, get_rsts, measure_clock, measure_temp, measure_volts, get_hvs_asserts, get_config, get_throttled, pmicrd, pmicwr, read_ring_osc, version, readmr, otp_dump, set_vll_dir, set_backlight, get_lcd_info, arbiter, test_result, get_camera, enable_clock, scaling_kernel, scaling_sharpness, hdmi_ntsc_freqs, hdmi_adjust_clock, hdmi_status_show, hvs_update_fields, pwm_speedup, force_audio, hdmi_stream_channels, hdmi_channel_map, display_power, memtest, dispmanx_list, schmoo, render_bar, disk_notify, inuse_notify, sus_suspend, sus_status, sus_is_enabled, sus_stop_test_thread, egl_platform_switch, mem_validate, mem_oom, mem_reloc_stats, hdmi_cvt, hdmi_timings, file, vcos, ap_output_control, ap_output_post_processing"

### More examples here

https://github.com/flype44/Emu68MailBoxResourceTest/tree/main

### Preview
<img width="687" height="1080" alt="image" src="Main.png" />
