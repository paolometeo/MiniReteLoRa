void readParamsFromFS()
{
  if (LittleFS.begin())
  {

    if (LittleFS.exists("/config.json"))
    {
      // file exists, reading and loading
      Serial.println("Reading config file");

      File configFile = LittleFS.open("/config.json", "r");
      if (configFile)
      {
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);

        DynamicJsonDocument json(256);
        auto deserializeError = deserializeJson(json, buf.get());
        serializeJson(json, Serial);
        Serial.println();
        if (!deserializeError)
        {

          if (json.containsKey("IO_USERNAME"))
            strcpy(IO_USERNAME, json["IO_USERNAME"]);
          if (json.containsKey("IO_KEY"))
            strcpy(IO_KEY, json["IO_KEY"]);
        }
        else
        {
          Serial.println("Failed to load json config");
        }
        configFile.close();
      }
    }

    else
    {
      Serial.println("Failed to mount FS");
    }
  }
}
