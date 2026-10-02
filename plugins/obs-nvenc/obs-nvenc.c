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
	 * Legacy NVENC compatibility:
	 * Do not run the OBS NVENC preflight as a module-load gate.
	 * Encoder registration is unconditional; the real NVENC API is
	 * exercised when the encoder is created.
	 */
	obs_nvenc_load();
	obs_cuda_load();

	return true;
}

void obs_module_unload(void)
{
	obs_cuda_unload();
	obs_nvenc_unload();
}
