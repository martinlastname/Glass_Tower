// See https://aka.ms/new-console-template for more information
using Raylib_cs;

namespace HelloWorld 
{
	static class Program
	{	
		public static void Main()
		{	
			Raylib.InitWindow(800, 480, "Hello World");

			// Needs to be some limit or else my graphics card freaks out.
			Raylib.SetTargetFPS(120);

			while (!Raylib.WindowShouldClose())
			{	
				Raylib.BeginDrawing();
				Raylib.ClearBackground(Color.WHITE);

				Raylib.DrawText("Hello, world!", 12, 12, 20, Color.BLACK);

				Raylib.EndDrawing(); 
			}

			Raylib.CloseWindow();
		}
	}
}
