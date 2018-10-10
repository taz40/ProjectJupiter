#include "pci.h"
#include "keyboard.h"
#include "mouse.h"

void printHex(uint32_t hex);
void terminal_writestring(const char* data);

PeripheralComponentInterconnectDeviceDescriptor::PeripheralComponentInterconnectDeviceDescriptor(){
    
}

PeripheralComponentInterconnectDeviceDescriptor::~PeripheralComponentInterconnectDeviceDescriptor(){
    
}

PeripheralComponentInterconnectController::PeripheralComponentInterconnectController()
:dataPort(0xCFC), commandPort(0xCF8){
    
}

PeripheralComponentInterconnectController::~PeripheralComponentInterconnectController(){
    
}

uint32_t PeripheralComponentInterconnectController::Read(uint16_t bus, uint16_t device, uint16_t function, uint32_t registeroffset){
    uint32_t id = 
        0x1 << 31
        | ((bus & 0xFF) << 16)
        | ((device & 0x1F) << 11)
        | ((function & 0x07) << 8)
        | (registeroffset & 0xFC);
        commandPort.Write(id);
        uint32_t result = dataPort.Read();
        return result >> (8*(registeroffset % 4));
}

void PeripheralComponentInterconnectController::Write(uint16_t bus, uint16_t device, uint16_t function, uint32_t registeroffset, uint32_t value){
    uint32_t id = 
        0x1 << 31
        | ((bus & 0xFF) << 16)
        | ((device & 0x1F) << 11)
        | ((function & 0x07) << 8)
        | (registeroffset & 0xFC);
        commandPort.Write(id);
        dataPort.Write(value);
}


bool PeripheralComponentInterconnectController::DevicehasFunctions(uint16_t bus, uint16_t device){
    return Read(bus, device, 0, 0x0E) & (1 << 7);
}

void PeripheralComponentInterconnectController::SelectDrivers(DriverManager* drivermanager, InterruptManager* interrupts){
    
    drivermanager->AddDriver(new MouseDriver(interrupts));
    drivermanager->AddDriver(new KeyboardDriver(interrupts));
    
    for(int bus = 0; bus < 8; bus++){
        for(int device = 0; device < 32; device++){
            int numfunctions = DevicehasFunctions(bus, device) ? 8 : 1;
            for(int function = 0; function < numfunctions; function++){
                PeripheralComponentInterconnectDeviceDescriptor descriptor = GetDeviceDescriptor(bus, device, function);
                if(descriptor.vendor_id == 0x00 || descriptor.vendor_id == 0xFFFF){
                    continue;
                }
                
                if(descriptor.class_id == 0x01 && descriptor.subclass_id == 0x01){
                    //printHex((Read(bus, device, function, 0)  << 4));
                }
                
                
            }
        }
    }
}

void PeripheralComponentInterconnectController::ListDevices(){
    for(int bus = 0; bus < 8; bus++){
        for(int device = 0; device < 32; device++){
            int numfunctions = DevicehasFunctions(bus, device) ? 8 : 1;
            for(int function = 0; function < numfunctions; function++){
                PeripheralComponentInterconnectDeviceDescriptor descriptor = GetDeviceDescriptor(bus, device, function);
                if(descriptor.vendor_id == 0x00 || descriptor.vendor_id == 0xFFFF){
                    continue;
                }
                
                terminal_writestring("PCI BUS ");
                printHex(bus);
                terminal_writestring(", DEVICE");
                printHex(device);
                terminal_writestring(", FUNCTION ");
                printHex(function);
                terminal_writestring(" = VENDOR ");
                printHex(descriptor.vendor_id);
                terminal_writestring(", DEVICE ");
                printHex(descriptor.device_id);
                terminal_writestring(", CLASS ");
                if(descriptor.class_id == 0x01){
                    terminal_writestring("mass storage controller");
                    terminal_writestring(", SUBCLASS ");
                    if(descriptor.subclass_id == 0x01){
                        terminal_writestring("IDE interface");
                    }else{
                        printHex(descriptor.subclass_id);
                    }
                }else if(descriptor.class_id == 0x06){
                    terminal_writestring("bridge");
                    terminal_writestring(", SUBCLASS ");
                    if(descriptor.subclass_id == 0x00){
                        terminal_writestring("Host bridge");
                    }else if(descriptor.subclass_id == 0x01){
                        terminal_writestring("ISA bridge");
                    }else if(descriptor.subclass_id == 0x80){
                        terminal_writestring("bridge");
                    }else{
                        printHex(descriptor.subclass_id);
                    }
                }else if(descriptor.class_id == 0x03){
                    terminal_writestring("display controller");
                    terminal_writestring(", SUBCLASS ");
                    if(descriptor.subclass_id == 0x00){
                        terminal_writestring("VGA compatible controller");
                    }else{
                        printHex(descriptor.subclass_id);
                    }
                }else if(descriptor.class_id == 0x02){
                    terminal_writestring("network controller");
                    terminal_writestring(", SUBCLASS ");
                    if(descriptor.subclass_id == 0x00){
                        terminal_writestring("Ethernet controller");
                    }else{
                        printHex(descriptor.subclass_id);
                    }
                }else if(descriptor.class_id == 0x08){
                    terminal_writestring("generic system peripheral");
                    terminal_writestring(", SUBCLASS ");
                    if(descriptor.subclass_id == 0x80){
                        terminal_writestring("system peripheral");
                    }else{
                        printHex(descriptor.subclass_id);
                    }
                }else if(descriptor.class_id == 0x04){
                    terminal_writestring("multimedia controller");
                    terminal_writestring(", SUBCLASS ");
                    if(descriptor.subclass_id == 0x01){
                        terminal_writestring("multimedia audio controller");
                    }else{
                        printHex(descriptor.subclass_id);
                    }
                }else if(descriptor.class_id == 0x0C){
                    terminal_writestring("serial bus controller");
                    terminal_writestring(", SUBCLASS ");
                    if(descriptor.subclass_id == 0x03){
                        terminal_writestring("USB controller");
                    }else{
                        printHex(descriptor.subclass_id);
                    }
                }else{
                    printHex(descriptor.class_id);
                    terminal_writestring(", SUBCLASS ");
                    printHex(descriptor.subclass_id);
                }
                terminal_writestring("\n");
                
                
            }
        }
    }
}

PeripheralComponentInterconnectDeviceDescriptor PeripheralComponentInterconnectController::GetDeviceDescriptor(uint16_t bus, uint16_t device, uint16_t function){
    PeripheralComponentInterconnectDeviceDescriptor result;
    
    result.bus = bus;
    result.device = device;
    result.function = function;
    
    result.vendor_id = Read(bus, device, function, 0x00);
    result.device_id = Read(bus, device, function, 0x02);
    
    result.class_id = Read(bus, device, function, 0x0B);
    result.subclass_id = Read(bus, device, function, 0xA);
    result.interface_id = Read(bus, device, function, 0x09);
    
    result.revision = Read(bus, device, function, 0x08);
    result.interrupt = Read(bus, device, function, 0x3C);
    
    return result;
}
