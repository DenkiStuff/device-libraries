#include "oled.h"
#include "oled_ll.h"

//  Covert a raw RGB triplet to a 16 bit, 565 struture needed by the SSD1331 control chip.
//  0bRRRRRGGGGGGBBBBB
uint16_t RGB8882RGB565(uint8_t red, uint8_t green, uint8_t blue, RGB565Scaling state)
{

  uint16_t rgb565pixel = 0x0000;

  if(state == Disabled){
    if (red > 31) red = 31;
    if (blue > 31) red = 31;
    if (green > 63) red = 63;
    rgb565pixel = ((uint16_t)red << 11) | ((uint16_t)green << 5) | (uint16_t)blue;
  } else {
      rgb565pixel = (uint16_t)(red>>3)<<11 | (uint16_t)(green>>2)<<11 | (uint16_t)(blue>>3);
  }
  return rgb565pixel;
}


void oled_clearscreen()
{
	// Set Command mode
	oled_ll_set_command_mode();

	// Clear the screen by sending the clear command and the dimensions of the window to clear (top column, top row, bottom column, bottom row).
	// Write 5 bytes-- the clear command and the five bytes representing the area to clear
	oled_ll_select_oled();
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x25);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x00);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x00);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(OLED_COL_WIDTH - 1U);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(OLED_ROW_HEIGHT - 1U);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	HAL_Delay(10);
	oled_ll_deselect_oled();
}



void oled_init()
{
	// Set Command mode
	oled_ll_set_command_mode();

	// bring pin high to to clear reset (initial set)
	oled_ll_clear_reset();

	// VCC Enable pin low to keep the screen off until control IC is configuired
	oled_ll_vccen_clear();

	// PMod Enable
	// Enable power to the control IC
	oled_ll_pmoden_set();

	// Reset the module
	oled_ll_reset();
	HAL_Delay(1); //at least 3 us
	oled_ll_clear_reset();
	HAL_Delay(1); //maximum of of 3 us needed

	// oled unlock command
	//Write two bytes-- the (un)lock commands register and the byte value to set the register to unlock command mode
	oled_ll_select_oled();
	while( !(oled_handle.State == HAL_SPI_STATE_READY) ); // wait UNTIL the TX buffer is NOT empty
	oled_ll_spi_senddata8(0xFD);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) ); // wait UNTIL the TX buffer is NOT empty
	oled_ll_spi_senddata8(0x12);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) ); // wait while SPI1 is busy
	oled_ll_deselect_oled();


 	// turn the display off
	oled_ll_select_oled();
	while( !(oled_handle.State == HAL_SPI_STATE_READY) ); 
	oled_ll_spi_senddata8(0xAE);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) ); 
	oled_ll_deselect_oled();


	// Check carefully for errors below this line--- nttenny
  	// Write two bytes-- the driver remap and color depth command and the single byte value
  	oled_ll_select_oled();
 	while( !(oled_handle.State == HAL_SPI_STATE_READY) ); 
  	oled_ll_spi_senddata8(0xA0);
  	while( !(oled_handle.State == HAL_SPI_STATE_READY) ); 
  	oled_ll_spi_senddata8(0x72);
  	while( !(oled_handle.State == HAL_SPI_STATE_READY) ); 
  	oled_ll_deselect_oled();


  	// Set the Display start Line to the top line
  	// Write two bytes-- the set display start line command and the single byte value for the top line
  	oled_ll_select_oled();
  	while( !(oled_handle.State == HAL_SPI_STATE_READY) ); 
  	oled_ll_spi_senddata8(0xA1);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) ); 
	oled_ll_spi_senddata8(0x00);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) ); 
	oled_ll_deselect_oled();

	// Set the Display Offset to no vertical offset
	// Write two bytes-- the  command and the single byte value for no vertical offset)
	oled_ll_select_oled();
	while( !(oled_handle.State == HAL_SPI_STATE_READY) ); 
	oled_ll_spi_senddata8(0xA2);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) ); 
	oled_ll_spi_senddata8(0x00);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) ); 
	oled_ll_deselect_oled();


	//  Make it a normal display with no color inversion or forcing the pixels on/off (0xA4).
	oled_ll_select_oled();
	while( !(oled_handle.State == HAL_SPI_STATE_READY) ); 
	oled_ll_spi_senddata8(0xA4);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) ); 
	oled_ll_deselect_oled();

	// Set the Multiplex Ratio to enable all of the common pins calculated by 1+register value (0xA8, 0x3F). See page 30 of the datasheet for more details
	// Write two bytes-- the multiplex ratio command and the single byte value
	oled_ll_select_oled();
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0xA8);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x3F);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_deselect_oled();

	// Set Master Configuration to use a required external Vcc supply (0xAD, 0x8E).
	// Write two bytes-- the master configuration command and the required single byte value of 0x8E
	oled_ll_select_oled();
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0xAD);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x8E);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_deselect_oled();

	// Disable Power Saving Mode
	// Write two bytes-- the power saving mode command and the single byte value
	oled_ll_select_oled();
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0xB0);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x0B);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_deselect_oled();

	// Set the Phase Length of the charge and discharge rates of an OLED pixel in units of the display clock See page 26 of the datasheet for more details.
	// Write two bytes-- the set phase length command and the single byte value
	oled_ll_select_oled();
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0xB1);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x31);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_deselect_oled();

	// Set the Display Clock Divide Ratio and Oscillator Frequency, setting the clock divider ratio to 1 and the internal oscillator frequency to ~890 kHz. See Figure 28 on page 46 of the datasheet for more details.
	// Write two bytes-- the Clock ratio and oscillator frequency command and the single byte value
	oled_ll_select_oled();
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0xB3);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0xF0);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_deselect_oled();

	// Set the Second Pre-Charge Speed of Color A¹ to drive the color (red by default) to a target driving voltage. See page 26 and 37 of the datasheet for more details.
	// Write two bytes-- the color A 2nd precharge speed command and the single byte value
	oled_ll_select_oled();
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x8A);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x64);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_deselect_oled();

	// Set the Second Pre-Charge Speed of Color B¹ to drive the color (green by default) to a target driving voltage. See page 26 and 37 of the datasheet for more details.
	// Write two bytes-- the color B 2nd precharge speed command and the single byte value
	oled_ll_select_oled();
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x8B);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x78);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_deselect_oled();

	// Set the Second Pre-Charge Speed of Color C¹ to drive the color (blue by default) to a target driving voltage. See page 26 and 37 of the datasheet for more details.
	// Write two bytes-- the color C 2nd precharge speed command and the single byte value
	oled_ll_select_oled();
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x8C);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x64);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_deselect_oled();

	// Set the Pre-Charge Voltage to approximately 45% of Vcc to drive each color to a target driving voltage. See Figure 30 on page 47 of the datasheet for the definition of approximate. More details about the pre-charge voltage are available on pages 26 and 37.
	// Write two bytes-- the set precharge voltage command and the single byte value
	oled_ll_select_oled();
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0xBB);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x3A);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_deselect_oled();

	// Set the VCOMH Deselect Level, which is the minimum voltage level to be registered as logic high, to 83% of Vcc.
	// Write two bytes-- the VCOMH Deselect level command and the single byte value
	oled_ll_select_oled();
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0xBE);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x3E);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_deselect_oled();

	// Set Master Current Attenuation Factor to set a reference current for the segment drivers. See page 23 of the datasheet for the equation and more details.
	// Write two bytes-- the set master current attenuation factor command and the single byte value
	oled_ll_select_oled();
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x87);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x06);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_deselect_oled();

	// Set the Contrast for Color A (default red), effectively setting the brightness level. See the 4th bullet point on page 23 of the datasheet for the associated equation and more details.
	// Write two bytes-- the Color A contrast command and the single byte value
	oled_ll_select_oled();
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x81);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x91);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_deselect_oled();

	// Set the Contrast for Color B (default green), effectively setting the brightness level. See the 4th bullet point on page 23 of the datasheet for the associated equation and more details.
	// Write two bytes-- the Color B contrast command and the single byte value
	oled_ll_select_oled();
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x82);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x50);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_deselect_oled();

	// Set the Contrast for Color C (default blue), effectively setting the brightness level. See the 4th bullet point on page 23 of the datasheet for the associated equation and more details.
	// Write two bytes-- the Color C contrast command and the single byte value
	oled_ll_select_oled();
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x83);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x7D);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_deselect_oled();

	// Disable Scrolling.
	oled_ll_select_oled();
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0x25);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_deselect_oled();

	// Bring VCC Enable high to enable the display
	// needs 25 ms to fully power on
	oled_ll_vccen_set();
	HAL_Delay(25);

	// Leave oled module in data mode
	oled_ll_set_data_mode();

	oled_clearscreen();

	// Set control IC to enable output
	// Write a single byte-- the turn display on command
	oled_ll_select_oled();
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(0xAF);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_deselect_oled();

	// Wait 100ms before any additional commands
	HAL_Delay(100);

	oled_clearscreen();

}

void oled_drawline (uint8_t col_start, uint8_t row_start, uint8_t col_end, uint8_t row_end, uint8_t red, uint8_t green, uint8_t blue)
{
  // Set Command mode
  oled_ll_set_command_mode();

  // Clear the screen by sending the clear command and the dimensions of the window to clear (top column, top row, bottom column, bottom row).
  // Write 5 bytes-- the clear command and the five bytes representing the area to clear
  oled_ll_select_oled();
  while( !(oled_handle.State == HAL_SPI_STATE_READY) );

  oled_ll_spi_senddata8(0x21);
  while( !(oled_handle.State == HAL_SPI_STATE_READY) );
  oled_ll_spi_senddata8(col_start);
  while( !(oled_handle.State == HAL_SPI_STATE_READY) );
  oled_ll_spi_senddata8(row_start);
  while( !(oled_handle.State == HAL_SPI_STATE_READY) );
  oled_ll_spi_senddata8(col_end);
  while( !(oled_handle.State == HAL_SPI_STATE_READY) );
  oled_ll_spi_senddata8(row_end);
  while( !(oled_handle.State == HAL_SPI_STATE_READY) );
  oled_ll_spi_senddata8(red);
  while( !(oled_handle.State == HAL_SPI_STATE_READY) );
  oled_ll_spi_senddata8(green);
  while( !(oled_handle.State == HAL_SPI_STATE_READY) );
  oled_ll_spi_senddata8(blue);

	// SPI de-select module
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_deselect_oled();
}

void oled_rawpixeldata(uint8_t col_start, uint8_t row_start, uint8_t col_end, uint8_t row_end, uint16_t * pixel_data_Array)
{

	uint8_t width = col_end - col_start + 1;
	uint8_t height = row_end - row_start + 1;
	uint16_t data_count = width * height;

	// Set Command mode
	oled_ll_set_command_mode();

	// SPI select module
	oled_ll_select_oled();

	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(CMD_SETCOLUMNADDRESS);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(col_start);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(col_end);


	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(CMD_SETROWADDRESS);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(row_start);
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_spi_senddata8(row_end);

	// SPI de-select module
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_deselect_oled();


	// Set data mode
	oled_ll_set_data_mode();

	// SPI select module
	oled_ll_select_oled();

	uint16_t count;
	for(count = 0; count < data_count; count++){
		while( !(oled_handle.State == HAL_SPI_STATE_READY) );
		oled_ll_spi_senddata8((uint8_t)( (*pixel_data_Array>>8) & 0x00FF));

		while( !(oled_handle.State == HAL_SPI_STATE_READY) );
		oled_ll_spi_senddata8((uint8_t)(*pixel_data_Array & 0x00FF));
		pixel_data_Array++;
	}

	// SPI de-select module
	while( !(oled_handle.State == HAL_SPI_STATE_READY) );
	oled_ll_deselect_oled();

}
