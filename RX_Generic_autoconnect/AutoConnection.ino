 void AutoConnection(){
 Serial.println("inizio collegamenti");
  flgwifi = 0; 
  WiFi.begin();
  readParamsFromFS();                      // get parameters from file system
  wifiManager.resetSettings();              //uncomment to reset the WiFi settings
  wifiManager.setClass("invert");          // enable "dark mode" for the config portal
  wifiManager.setConfigPortalTimeout(120); // auto close configportal after n seconds
  wifiManager.setAPClientCheck(true);      // avoid timeout if client connected to softap
  wifiManager.addParameter(&custom_IO_USERNAME); // set custom parameter for IO username
  wifiManager.addParameter(&custom_IO_KEY);      // set custom parameter for IO key

  custom_IO_KEY.setValue(IO_KEY, 64);           // set custom parameter value
  custom_IO_USERNAME.setValue(IO_USERNAME, 64); // set custom parameter value

  wifiManager.setSaveConfigCallback(saveConfigCallback); // set config save notify callback

  if (!wifiManager.autoConnect("WiFi Setup")) // connect to wifi with existing setting or start config
  {
    Serial.println("Failed to connect and hit timeout");
  }
  else
  {
    // if you get here you have connected to the WiFi
    Serial.println("Connected to WiFi.");

    // connect to Adafruit IO
  //  Serial.println(IO_USERNAME);
   // Serial.println(IO_KEY);
    io = new (objStorage) AdafruitIO_WiFi(IO_USERNAME, IO_KEY, "", "");

    Serial.printf("Connecting to Adafruit IO with User: %s Key: %s.\n", IO_USERNAME, IO_KEY);

    io->connect();
  //AdafruitIO_Feed *Temp = io->feed("Temp");
    while ((io->status() < AIO_CONNECTED))
    {
      Serial.print(".");
      delay(500);
    }
    Serial.println("Connected to Adafruit IO.");
    flgwifi = 1;
  }
 }  
