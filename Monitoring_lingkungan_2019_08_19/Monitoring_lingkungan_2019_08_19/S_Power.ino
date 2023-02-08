void daya()
{
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  Current = ina219.getCurrent_mA();
  Voltage = busvoltage + (shuntvoltage / 1000);
  Power = ina219.getPower_mW();
  Energy=Energy+Power*(0.5/3600);
}
