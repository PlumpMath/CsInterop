using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace CsInterop
{
	public class Commands
	{
		static Commands()
		{
			Open = new RoutedUICommand("_Open", "open", typeof(Commands),
				new InputGestureCollection
				{
					new KeyGesture(Key.O, ModifierKeys.Control, "Ctrl+O")
				});

			Save = new RoutedUICommand("_Save", "save", typeof(Commands),
				new InputGestureCollection
				{
					new KeyGesture(Key.S, ModifierKeys.Control, "Ctrl+S")
				});

			Exit = new RoutedUICommand("E_xit", "exit", typeof(Commands),
				new InputGestureCollection
				{
					new KeyGesture(Key.Q, ModifierKeys.Control, "Ctrl+Q")
				});
		}

		public static RoutedUICommand Open { get; private set; }
		public static RoutedUICommand Save { get; private set; }
		public static RoutedUICommand Exit { get; private set; }
	}
}
