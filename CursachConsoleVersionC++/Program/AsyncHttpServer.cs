using System;
using System.IO;
using System.Net;
using System.Threading;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace Program
{
    internal class AsyncHttpServer : IDisposable
    {
        public AsyncHttpServer()
        {
            listener = new HttpListener();
        }

        public void Start(string prefix)
        {
            lock (listener)
            {
                if (!isRunning)
                {
                    listener.Prefixes.Clear();
                    listener.Prefixes.Add(prefix);
                    listener.Start();

                    listenerThread = new Thread(Listen)
                    {
                        IsBackground = true,
                        Priority = ThreadPriority.Highest
                    };
                    listenerThread.Start();

                    isRunning = true;
                }
            }
        }

        public void Stop()
        {
            lock (listener)
            {
                if (!isRunning)
                    return;

                listener.Stop();

                listenerThread.Abort();
                listenerThread.Join();

                isRunning = false;
            }
        }

        public void Dispose()
        {
            if (disposed)
                return;

            disposed = true;

            Stop();

            listener.Close();
        }

        private void Listen()
        {
            while (true)
            {
                try
                {
                    if (listener.IsListening)
                    {
                        var context = listener.GetContext();
                        Task.Run(() => HandleContextAsync(context));
                    }
                    else Thread.Sleep(0);
                }
                catch (ThreadAbortException)
                {
                    return;
                }
                catch (Exception)
                {
                    continue;
                }
            }
        }

        private async Task HandleContextAsync(HttpListenerContext listenerContext)
        {
            try
            {
                Console.WriteLine(listenerContext.Request.RawUrl);
                listenerContext.Response.StatusCode = (int)HttpStatusCode.OK;
            }
            catch (ArgumentException)
            {
                listenerContext.Response.StatusCode = (int)HttpStatusCode.BadRequest;
            }
            catch (InvalidOperationException)
            {
                listenerContext.Response.StatusCode = (int)HttpStatusCode.NoContent;
            }
            catch (Exception)
            {
                listenerContext.Response.StatusCode = (int)HttpStatusCode.BadRequest;
            }
            finally
            {
                if (listenerContext.Response.OutputStream.CanWrite)
                    listenerContext.Response.OutputStream.Close();
            }
        }
        
        private void ParseUrl(string url)
        {
        }

        // делегат обработки пикселя
        private delegate void PixelChange(ref int r, ref int g, ref int b, int x = -1);

        private readonly HttpListener listener;

        private Thread listenerThread;
        private bool disposed;
        private volatile bool isRunning;
    }
}