using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace CsInterop
{
	class Interop
	{
		[DllImport("file.dll")]
		public static extern void writeToFile([MarshalAs(UnmanagedType.AnsiBStr)]string filename, [MarshalAs(UnmanagedType.AnsiBStr)]string content);

		[DllImport("file.dll")]
		public static extern IntPtr readFromFile([MarshalAs(UnmanagedType.AnsiBStr)]string filename);

		public static string marshal(IntPtr ptr)
		{
			return Marshal.PtrToStringAnsi(ptr);
		}
	}
}
