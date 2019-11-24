class message{
  byte _destination;
  byte _source;
  byte _event;
  byte _cars_N;
  byte _cars_S;
  byte _cars_E;
  byte _cars_W;
  long _time_stamp;

  public:
  message(byte destination,byte source,byte event,byte cars_N,byte cars_S,byte cars_E,byte cars_W ){
    _destination = destination;
    _source = source;
    _event = event;
    _cars_N = cars_N;
    _cars_S = cars_S;
    _cars_E = cars_E;
    _cars_W = cars_W;
    
  }
  void get_sended(){
    Wire.beginTransmission();
    Wire.write((byte) _destination);
    Wire.write((byte) _source);
    Wire.write((byte) _event);
    Wire.write((byte) _cars_N);
    Wire.write((byte) _cars_S);
    Wire.write((byte) _cars_E);
    Wire.write((byte) _cars_W);
    _time_stamp = millis();
    Wire.write((byte)(_time_stamp>>24));
    Wire.write((byte)(_time_stamp>>16));
    Wire.write((byte)(_time_stamp>>8));
    Wire.write((byte) _time_stamp);
    Wire.endTransmission();
  }
  recieve(int numBytes)
  {  
    _destination = (byte)Wire.read();
    _source = (byte)Wire.read(); 
    _cars_N = (byte)Wire.read();
    _cars_S = (byte)Wire.read();
    _cars_E = (byte)Wire.read();
    _cars_W = (byte)Wire.read();
    _time_stamp = (long)Wire.read();
    _time_stamp = (_time_stamp<<8) + Wire.read(); 
    _time_stamp = (_time_stamp<<8) + Wire.read(); 
    _time_stamp = (_time_stamp<<8) + Wire.read(); 
  }

  
}
