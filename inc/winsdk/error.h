#pragma once

#include "base.h"

extern "C"
{
namespace winsdk
{
    // Constants
    constexpr std::int32_t facility_null = 0;
    constexpr std::int32_t facility_rpc = 1;
    constexpr std::int32_t facility_dispatch = 2;
    constexpr std::int32_t facility_storage = 3;
    constexpr std::int32_t facility_itf = 4;
    constexpr std::int32_t facility_win32 = 7;
    constexpr std::int32_t facility_windows = 8;
    constexpr std::int32_t facility_sspi = 9;
    constexpr std::int32_t facility_security = 9;
    constexpr std::int32_t facility_control = 10;
    constexpr std::int32_t facility_cert = 11;
    constexpr std::int32_t facility_internet = 12;
    constexpr std::int32_t facility_mediaserver = 13;
    constexpr std::int32_t facility_msmq = 14;
    constexpr std::int32_t facility_setupapi = 15;
    constexpr std::int32_t facility_scard = 16;
    constexpr std::int32_t facility_complus = 17;
    constexpr std::int32_t facility_aaf = 18;
    constexpr std::int32_t facility_urt = 19;
    constexpr std::int32_t facility_acs = 20;
    constexpr std::int32_t facility_dplay = 21;
    constexpr std::int32_t facility_umi = 22;
    constexpr std::int32_t facility_sxs = 23;
    constexpr std::int32_t facility_windows_ce = 24;
    constexpr std::int32_t facility_http = 25;
    constexpr std::int32_t facility_usermode_commonlog = 26;
    constexpr std::int32_t facility_wer = 27;
    constexpr std::int32_t facility_usermode_filter_manager = 31;
    constexpr std::int32_t facility_backgroundcopy = 32;
    constexpr std::int32_t facility_configuration = 33;
    constexpr std::int32_t facility_wia = 33;
    constexpr std::int32_t facility_state_management = 34;
    constexpr std::int32_t facility_metadirectory = 35;
    constexpr std::int32_t facility_windowsupdate = 36;
    constexpr std::int32_t facility_directoryservice = 37;
    constexpr std::int32_t facility_graphics = 38;
    constexpr std::int32_t facility_shell = 39;
    constexpr std::int32_t facility_nap = 39;
    constexpr std::int32_t facility_tpm_services = 40;
    constexpr std::int32_t facility_tpm_software = 41;
    constexpr std::int32_t facility_ui = 42;
    constexpr std::int32_t facility_xaml = 43;
    constexpr std::int32_t facility_action_queue = 44;
    constexpr std::int32_t facility_pla = 48;
    constexpr std::int32_t facility_windows_setup = 48;
    constexpr std::int32_t facility_fve = 49;
    constexpr std::int32_t facility_fwp = 50;
    constexpr std::int32_t facility_winrm = 51;
    constexpr std::int32_t facility_ndis = 52;
    constexpr std::int32_t facility_usermode_hypervisor = 53;
    constexpr std::int32_t facility_cmi = 54;
    constexpr std::int32_t facility_usermode_virtualization = 55;
    constexpr std::int32_t facility_usermode_volmgr = 56;
    constexpr std::int32_t facility_bcd = 57;
    constexpr std::int32_t facility_usermode_vhd = 58;
    constexpr std::int32_t facility_usermode_hns = 59;
    constexpr std::int32_t facility_sdiag = 60;
    constexpr std::int32_t facility_webservices = 61;
    constexpr std::int32_t facility_winpe = 61;
    constexpr std::int32_t facility_wpn = 62;
    constexpr std::int32_t facility_windows_store = 63;
    constexpr std::int32_t facility_input = 64;
    constexpr std::int32_t facility_eap = 66;
    constexpr std::int32_t facility_windows_defender = 80;
    constexpr std::int32_t facility_opc = 81;
    constexpr std::int32_t facility_xps = 82;
    constexpr std::int32_t facility_mbn = 84;
    constexpr std::int32_t facility_powershell = 84;
    constexpr std::int32_t facility_ras = 83;
    constexpr std::int32_t facility_p2p_int = 98;
    constexpr std::int32_t facility_p2p = 99;
    constexpr std::int32_t facility_daf = 100;
    constexpr std::int32_t facility_bluetooth_att = 101;
    constexpr std::int32_t facility_audio = 102;
    constexpr std::int32_t facility_staterepository = 103;
    constexpr std::int32_t facility_visualcpp = 109;
    constexpr std::int32_t facility_script = 112;
    constexpr std::int32_t facility_parse = 113;
    constexpr std::int32_t facility_blb = 120;
    constexpr std::int32_t facility_blb_cli = 121;
    constexpr std::int32_t facility_wsbapp = 122;
    constexpr std::int32_t facility_blbui = 128;
    constexpr std::int32_t facility_usn = 129;
    constexpr std::int32_t facility_usermode_volsnap = 130;
    constexpr std::int32_t facility_tiering = 131;
    constexpr std::int32_t facility_wsb_online = 133;
    constexpr std::int32_t facility_online_id = 134;
    constexpr std::int32_t facility_device_update_agent = 135;
    constexpr std::int32_t facility_drvservicing = 136;
    constexpr std::int32_t facility_dls = 153;
    constexpr std::int32_t facility_delivery_optimization = 208;
    constexpr std::int32_t facility_usermode_spaces = 231;
    constexpr std::int32_t facility_user_mode_security_core = 232;
    constexpr std::int32_t facility_usermode_licensing = 234;
    constexpr std::int32_t facility_sos = 160;
    constexpr std::int32_t facility_debuggers = 176;
    constexpr std::int32_t facility_spp = 256;
    constexpr std::int32_t facility_restore = 256;
    constexpr std::int32_t facility_dmserver = 256;
    constexpr std::int32_t facility_deployment_services_server = 257;
    constexpr std::int32_t facility_deployment_services_imaging = 258;
    constexpr std::int32_t facility_deployment_services_management = 259;
    constexpr std::int32_t facility_deployment_services_util = 260;
    constexpr std::int32_t facility_deployment_services_binlsvc = 261;
    constexpr std::int32_t facility_deployment_services_pxe = 263;
    constexpr std::int32_t facility_deployment_services_tftp = 264;
    constexpr std::int32_t facility_deployment_services_transport_management = 272;
    constexpr std::int32_t facility_deployment_services_driver_provisioning = 278;
    constexpr std::int32_t facility_deployment_services_multicast_server = 289;
    constexpr std::int32_t facility_deployment_services_multicast_client = 290;
    constexpr std::int32_t facility_deployment_services_content_provider = 293;
    constexpr std::int32_t facility_linguistic_services = 305;
    constexpr std::int32_t facility_audiostreaming = 1094;
    constexpr std::int32_t facility_accelerator = 1536;
    constexpr std::int32_t facility_wmaaecma = 1996;
    constexpr std::int32_t facility_directmusic = 2168;
    constexpr std::int32_t facility_direct3d10 = 2169;
    constexpr std::int32_t facility_dxgi = 2170;
    constexpr std::int32_t facility_dxgi_ddi = 2171;
    constexpr std::int32_t facility_direct3d11 = 2172;
    constexpr std::int32_t facility_direct3d11_debug = 2173;
    constexpr std::int32_t facility_direct3d12 = 2174;
    constexpr std::int32_t facility_direct3d12_debug = 2175;
    constexpr std::int32_t facility_leap = 2184;
    constexpr std::int32_t facility_audclnt = 2185;
    constexpr std::int32_t facility_wincodec_dwrite_dwm = 2200;
    constexpr std::int32_t facility_winml = 2192;
    constexpr std::int32_t facility_direct2d = 2201;
    constexpr std::int32_t facility_defrag = 2304;
    constexpr std::int32_t facility_usermode_sdbus = 2305;
    constexpr std::int32_t facility_jscript = 2306;
    constexpr std::int32_t facility_pidgenx = 2561;
    constexpr std::int32_t facility_eas = 85;
    constexpr std::int32_t facility_web = 885;
    constexpr std::int32_t facility_web_socket = 886;
    constexpr std::int32_t facility_mobile = 1793;
    constexpr std::int32_t facility_sqlite = 1967;
    constexpr std::int32_t facility_utc = 1989;
    constexpr std::int32_t facility_wep = 2049;
    constexpr std::int32_t facility_syncengine = 2050;
    constexpr std::int32_t facility_xbox = 2339;
    constexpr std::int32_t facility_game = 2340;
    constexpr std::int32_t facility_pix = 2748;
}
}

namespace winsdk
{
    inline constexpr std::int32_t hresult_facility(std::int32_t hr) noexcept
    {
        return (hr >> 16) & 0x1FFF;
    }

    inline constexpr std::int32_t hresult_code(std::int32_t hr) noexcept
    {
        return hr & 0xFFFF;
    }
}
