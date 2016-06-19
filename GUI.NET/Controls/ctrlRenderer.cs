﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Mesen.GUI.Config;

namespace Mesen.GUI.Controls
{
	public partial class ctrlRenderer : UserControl
	{
		private bool _cursorHidden = false;

		public ctrlRenderer()
		{
			InitializeComponent();
		}

		private void ShowMouse()
		{
			if(_cursorHidden) {
				Cursor.Show();
				_cursorHidden = false;
			}
		}

		private void HideMouse()
		{
			if(!_cursorHidden) {
				Cursor.Hide();
				_cursorHidden = true;
			}
		}
		
		protected override void OnDoubleClick(EventArgs e)
		{
			if(!InteropEmu.HasZapper()) {
				//Disable double clicking (used to switch to fullscreen mode) when using zapper
				base.OnDoubleClick(e);
			}
		}

		private void ctrlRenderer_MouseMove(object sender, MouseEventArgs e)
		{
			if(!InteropEmu.IsRunning() || InteropEmu.IsPaused() || !InteropEmu.HasArkanoidPaddle()) {
				ShowMouse();
			} else if(InteropEmu.HasArkanoidPaddle() && !InteropEmu.HasZapper()) {
				HideMouse();
			}

			tmrMouse.Stop();

			if(InteropEmu.HasZapper()) {
				this.Cursor = Cursors.Cross;
			} else {
				this.Cursor = Cursors.Default;

				//Only hide mouse if no zapper (otherwise this could be pretty annoying)
				tmrMouse.Start();
			}

			double xPos = (double)e.X / this.Width;
			double yPos = (double)e.Y / this.Height;

			xPos = Math.Max(0.0, Math.Min(1.0, xPos));
			yPos = Math.Max(0.0, Math.Min(1.0, yPos));

			InteropEmu.SetMousePosition(xPos, yPos);
		}
		
		private void tmrMouse_Tick(object sender, EventArgs e)
		{
			HideMouse();
		}

		private void ctrlRenderer_MouseLeave(object sender, EventArgs e)
		{
			tmrMouse.Stop();
			ShowMouse();
		}
	}
}
