// Copyright Epic Games, Inc. All Rights Reserved.

#include "HTTPRequestPlugin.h"

#define LOCTEXT_NAMESPACE "FHTTPRequestPluginModule"

void FHTTPRequestPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FHTTPRequestPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}


bool FHTTPRequestPluginModule::SupportsDynamicReloading()
{
	return true;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHTTPRequestPluginModule, HTTPRequestPlugin)