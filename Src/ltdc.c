#include "ltdc.h"

extern LTDC_HandleTypeDef hltdc;

//————————————————
void TFT_FillScreen_565(uint32_t color)
{
	uint32_t i;
	uint32_t n = hltdc.LayerCfg[0].ImageHeight*hltdc.LayerCfg[0].ImageWidth;
	for(i=0;i<n;i++)
	 {
	  *(__IO uint16_t*) (hltdc.LayerCfg[0].FBStartAdress + (i*2)) = (uint16_t) color;
	 }
}
//————————————————

void TFT_FillScreen(uint32_t color)
{
 uint32_t i;
 uint32_t n = hltdc.LayerCfg[0].ImageHeight*hltdc.LayerCfg[0].ImageWidth;
 for(i=0;i<n;i++)
 {
  *(__IO uint32_t*) (hltdc.LayerCfg[0].FBStartAdress + (i*4)) = color;
 }
}
//————————————————

void TFT_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint32_t color)
{
 *(__IO uint32_t*) (hltdc.LayerCfg[0].FBStartAdress +
		 (4*(Ypos*hltdc.LayerCfg[0].ImageWidth + Xpos))) = color;
}
//————————————————

void TFT_FillRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color)
{
 uint32_t xpos, ypos;
 uint16_t buf;
 if (x1 > x2)
	 {
	 	 buf = x1; x1 = x2; x2 = buf;
	 }
 if (y1 > y2)
 	 {
 	 	 buf = y1; y1 = y2; y2 = buf;
 	 }
 for(ypos = y1;ypos <= y2;ypos++)
 {
  for(xpos = x1;xpos <= x2;xpos++)
  {
   *(__IO uint32_t*) (hltdc.LayerCfg[0].FBStartAdress + (4*(ypos*hltdc.LayerCfg[0].ImageWidth + xpos))) = color;
  }
 }
}
//————————————————
