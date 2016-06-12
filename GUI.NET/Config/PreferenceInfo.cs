﻿using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Mesen.GUI.Forms;
using Microsoft.Win32;

namespace Mesen.GUI.Config
{
	public class PreferenceInfo
	{
		public Language DisplayLanguage = Language.SystemDefault;

		public bool SingleInstance = true;
		public bool PauseWhenInBackground = false;
		public bool AllowBackgroundInput = false;
		public bool AutoLoadIpsPatches = true;
		public bool AllowInvalidInput = false;
		public bool RemoveSpriteLimit = false;

		public bool FdsAutoLoadDisk = true;
		public bool FdsFastForwardOnLoad = false;

		public bool AssociateNesFiles = false;
		public bool AssociateFdsFiles = false;
		public bool AssociateMmoFiles = false;
		public bool AssociateMstFiles = false;

		public bool PauseOnMovieEnd = true;
		public bool AutomaticallyCheckForUpdates = true;

		public bool UseAlternativeMmc3Irq = false;

		public bool CloudSaveIntegration = false;
		public DateTime CloudLastSync = DateTime.MinValue;

		public UInt32 OverclockRate = 100;
		public bool OverclockAdjustApu = true;

		public PreferenceInfo()
		{
		}

		static private void UpdateFileAssociation(string extension, bool associate)
		{
			string key = @"HKEY_CURRENT_USER\Software\Classes\." + extension;
			if(associate) {
				Registry.SetValue(@"HKEY_CURRENT_USER\Software\Classes\Mesen\shell\open\command", null, Application.ExecutablePath + " \"%1\"");
				Registry.SetValue(key, null, "Mesen");
			} else {
				//Unregister Mesen if Mesen was registered for .nes files
				object regKey = Registry.GetValue(key, null, "");
				if(regKey != null && regKey.Equals("Mesen")) {
					Registry.SetValue(key, null, "");
				}
			}
		}

		static public void ApplyConfig()
		{
			PreferenceInfo preferenceInfo = ConfigManager.Config.PreferenceInfo;
			
			UpdateFileAssociation("nes", preferenceInfo.AssociateNesFiles);
			UpdateFileAssociation("fds", preferenceInfo.AssociateFdsFiles);
			UpdateFileAssociation("mmo", preferenceInfo.AssociateMmoFiles);
			UpdateFileAssociation("mst", preferenceInfo.AssociateMstFiles);

			InteropEmu.SetFlag(EmulationFlags.Mmc3IrqAltBehavior, preferenceInfo.UseAlternativeMmc3Irq);
			InteropEmu.SetFlag(EmulationFlags.AllowInvalidInput, preferenceInfo.AllowInvalidInput);
			InteropEmu.SetFlag(EmulationFlags.RemoveSpriteLimit, preferenceInfo.RemoveSpriteLimit);
			InteropEmu.SetFlag(EmulationFlags.FdsAutoLoadDisk, preferenceInfo.FdsAutoLoadDisk);
			InteropEmu.SetFlag(EmulationFlags.FdsFastForwardOnLoad, preferenceInfo.FdsFastForwardOnLoad);
			InteropEmu.SetFlag(EmulationFlags.PauseOnMovieEnd, preferenceInfo.PauseOnMovieEnd);
			InteropEmu.SetFlag(EmulationFlags.AllowBackgroundInput, preferenceInfo.AllowBackgroundInput);
			InteropEmu.SetFlag(EmulationFlags.PauseWhenInBackground, preferenceInfo.PauseWhenInBackground);

			InteropEmu.SetOverclockRate(preferenceInfo.OverclockRate, preferenceInfo.OverclockAdjustApu);
		}
	}
}
