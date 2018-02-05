struct Timer {
      unsigned long start;
      bool running;
      
      Timer();
      
      void Toggle();
      int GetDuration();
}