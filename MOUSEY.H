

	int readstick(int);				// Read joystick position
	int readjbutton(int);			// Read joystick button
	extern "C"
	{
		 int	initmouse(void);					// Initialize mouse driver
	}
	void rempointer(void);				// Remove mouse pointer from display
	extern "C"
	{
		int readmbutton(void);				// Read mouse buttons
	}
	extern "C"
	{
		void relpos(int *,int *);	// Get relative mouse position
	}
	int	scankey(void);						// Get keyboard scan code

