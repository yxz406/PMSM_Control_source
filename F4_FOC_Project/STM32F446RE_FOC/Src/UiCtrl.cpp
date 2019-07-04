/*
 * UiCtrl.cpp
 *
 *  Created on: Jun 28, 2019
 *      Author: watashi
 */

/*
 * せつめい！
 * UI周りの歯痒い操作をここで管理する。
 * 例:トグルの情報を記憶
 * 例:長押しの処理の変化
 *
 * 個人的にオブジェクト志向が一番活躍するのはここだと思ってる。
 * いくら機能追加しても、Getter通して読み出せば良いだけだから、基本的な構造は崩れない。
 * (逆に機能が動作するClassに個別にこれらを処理する関数を持たせると、カプセル化しにくい。)
 */

#include "UiCtrl.hpp"

UiCtrl::UiCtrl() {
	// TODO Auto-generated constructor stub
	isONBtnState = false;
}

UiCtrl::~UiCtrl() {
	// TODO Auto-generated destructor stub
}

void UiCtrl::BtnAct(){
	if(isONBtnState == true){//ONの時
		isONBtnState = false;//offにするタスク
	} else {
		isONBtnState = true;//ONにするタスク
	}
}

bool UiCtrl::getState(void){return isONBtnState;}
