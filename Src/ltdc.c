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
