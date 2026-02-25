using System.IO.Ports;
using System.Management;

namespace LCDClock
{
    public class LCDClock
    {
        private const int DEFAULT_TIMEOUT = 10;
        private const int BAUD_RATE = 9600;
        private const int READ_TIMEOUT = DEFAULT_TIMEOUT * 3;
        private const int WRITE_TIMEOUT = DEFAULT_TIMEOUT * 3;

        public static void Main(string[] args)
        {
            SerialPort serialPort = new SerialPort();
            serialPort.PortName = GetArduinoComPort();
            serialPort.BaudRate = BAUD_RATE;
            serialPort.ReadTimeout = READ_TIMEOUT;
            serialPort.WriteTimeout = WRITE_TIMEOUT;

            // Aktuelle Zeit ermitteln
            string timeForSync = DateTime.Now.ToString("HH:mm:ss");

            Console.WriteLine("Aktuelle Zeit ist: " + timeForSync);

            try
            {
                serialPort.Open();
                Thread.Sleep(500);
                serialPort.Write(timeForSync);
                serialPort.Close();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
                Console.WriteLine("press any key to exit...");
                Console.ReadLine();
            }

            Console.WriteLine("Sync erfolgreich!");
        }

        /// <summary>
        /// Sucht nach einem Arduino Uno und gibt den ComPort zurück.
        /// </summary>
        /// <remarks>
        /// <br>Achtung! Es darf nur ein Arduino Uno angeschlossen sein.</br>
        /// <br>Sollten mehrere angeschlossen sein, dann muss Ident separat erfolgen.</br>
        /// </remarks>
        /// <returns>Comport des Arduino Uno.</returns>
        /// <exception cref="Exception"></exception>
        internal static string GetArduinoComPort()
        {
            string portName = string.Empty;
            var searcher = new ManagementObjectSearcher("SELECT * FROM Win32_SerialPort");
            foreach (ManagementObject result in searcher.Get())
            {
                Console.WriteLine(result["Caption"].ToString());
                Console.WriteLine(result["DeviceID"].ToString());
                if (result["Caption"].ToString().Contains("Arduino Uno"))
                {
                    portName = result["DeviceID"].ToString();
                    Console.WriteLine($"Arduino gefunden auf {portName}");
                }
            }
            if (portName == "")
            {
                throw new Exception("ERROR: Arduino Uno konnte an keinem COM-Port gefunden werden!");
            }

            return portName;
        }
    }
}

