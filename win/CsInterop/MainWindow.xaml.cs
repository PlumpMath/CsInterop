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
		}

		private void bSave_Click(object sender, RoutedEventArgs e)
		{
			save();
		}

		private void CommandBinding_CanExecute(object sender, CanExecuteRoutedEventArgs e)
		{
			e.CanExecute = true;
		}

		private void CommandOpen_Executed(object sender, ExecutedRoutedEventArgs e)
		{
			WF.OpenFileDialog ofd = new WF.OpenFileDialog();
			ofd.InitialDirectory = Assembly.GetExecutingAssembly().Location;
			if (ofd.ShowDialog() == WF.DialogResult.OK)
			{
				if (File.Exists(ofd.FileName))
				{
					tbFilename.Text = ofd.FileName;
					tbContent.Text = Interop.marshal(Interop.readFromFile(ofd.FileName));
				}
				else
				{
					MessageBox.Show(ofd.FileName + " could not be found!", "I/O Error", MessageBoxButton.OK, MessageBoxImage.Error);
				}
			}
		}

		private void CommandSave_Executed(object sender, ExecutedRoutedEventArgs e)
		{
			save();
		}

		private void CommandExit_Executed(object sender, ExecutedRoutedEventArgs e)
		{
			App.Current.Shutdown();
		}

		private void save()
		{
			if (tbFilename.Text.Equals(""))
			{
				MessageBox.Show("Cannot be empty!", "ERROR");
			}
			else
			{
				Interop.writeToFile(tbFilename.Text, tbContent.Text);
			}
		}
	}
}
