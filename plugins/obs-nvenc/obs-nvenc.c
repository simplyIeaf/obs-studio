#include <obs-module.h>

#include "obs-nvenc.h"

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("obs-nvenc", "en-US")

MODULE_EXPORT const char *obs_module_description(void)
{
	return "NVIDIA Encoder (NVENC) Plugin";
}

bool obs_module_load(void)
{
	/*
	 * Legacy/Kepler compatibility: do not use the preflight capability
	 * check as a module-load gate. Let real NVENC initialization decide.
	 */
	if (!nvenc_supported())
		blog(LOG_WARNING, "[obs-nvenc] Preflight reports NVENC unsupported; forcing encoder registration for legacy compatibility");

	obs_nvenc_load();
	obs_cuda_load();

	return true;
}

void obs_module_unload(void)
{
	obs_cuda_unload();
	obs_nvenc_unload();
}
