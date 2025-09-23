program ICDILight;

uses
  Forms,
  Unit1 in 'Unit1.pas' {Form1},
  PCANLight in 'PCANLight.pas',
  pcan_2isa in 'PCAN Includes\pcan_2isa.pas',
  pcan_2pcc in 'PCAN Includes\pcan_2pcc.pas',
  pcan_2pci in 'PCAN Includes\pcan_2pci.pas',
  pcan_2usb in 'PCAN Includes\pcan_2usb.pas',
  pcan_dng in 'PCAN Includes\pcan_dng.pas',
  pcan_dnp in 'PCAN Includes\pcan_dnp.pas',
  pcan_isa in 'PCAN Includes\pcan_isa.pas',
  pcan_pcc in 'PCAN Includes\pcan_pcc.pas',
  pcan_pci in 'PCAN Includes\pcan_pci.pas',
  pcan_usb in 'PCAN Includes\pcan_usb.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
