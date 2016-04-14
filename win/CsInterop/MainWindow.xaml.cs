using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;

using WF = System.Windows.Forms;
using System.Reflection;

namespace CsInterop
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
		public MainWindow()
		{
			InitializeComponent();

			Task.Factory.StartNew(() => { v_ofd(); });
		}

		private void bSave_Click(object sender, RoutedEventArgs e)
		{
			if(tbFilename.Text.Equals(""))
			{
				MessageBox.Show("Cannot be empty!", "ERROR");
			}
			else
			{
				Interop.writeToFile(tbFilename.Text, tbContent.Text);
			}
		}

		private delegate void d_ofd();
		private void v_ofd()
		{
			if (!Dispatcher.CheckAccess())
				Dispatcher.Invoke(new d_ofd(v_ofd));
			else
			{
				WF.OpenFileDialog ofd = new WF.OpenFileDialog();
				ofd.InitialDirectory = Assembly.GetExecutingAssembly().Location;
				if (ofd.ShowDialog() == WF.DialogResult.OK)
				{
					if (File.Exists(ofd.FileName))
					{
						settb(ofd.FileName);
					}
					else
					{
						MessageBox.Show(ofd.FileName + " could not be found!", "I/O Error", MessageBoxButton.OK, MessageBoxImage.Error);
					}
				}
			}
		}

		private delegate void d_settb(string filename);
		private void settb(string filename)
		{
			if(!Dispatcher.CheckAccess())
				Dispatcher.Invoke(new d_settb(settb), filename);
			else
			{
				tbFilename.Text = filename;
				tbContent.Text = Interop.marshal(Interop.readFromFile(filename));
			}
		}
	}
}
