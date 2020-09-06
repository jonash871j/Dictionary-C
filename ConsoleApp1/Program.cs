using System;
using System.Runtime.InteropServices;

namespace ConsoleApp1
{
    class Program
    {
        [DllImport("dict C.dll")]
            static extern IntPtr inn_dictionary_init(uint _key_sizeof, uint _value_sizeof);

        static void Main(string[] args)
        {
            IntPtr dictionary = inn_dictionary_init(4, 4);
            Console.WriteLine("Hello World!");
        }
    }
}
