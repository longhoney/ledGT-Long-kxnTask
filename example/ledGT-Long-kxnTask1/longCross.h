#ifndef longCross__H
#define longCross__H
#include "kxnTask.h"

DEFINE_TASK_STATE(longCross) //thu vien "kxnTask.h"
{
  longCross_ON_R,  //sang den do
  longCross_ON_Y,  //sang den vang
  longCross_ON_G,  //sang den xanh
  longCross_ON_Y1,  //bien dem
  longCross_ON_G1,  //bien dem
  longCross_OFF
};

CREATE_TASK(longCross)

END
#endif