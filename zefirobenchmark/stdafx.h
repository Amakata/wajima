// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
//

#pragma once

#define WIN32_LEAN_AND_MEAN		// Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
// Windows �w�b�_�[ �t�@�C�� :
#include <windows.h>
#include <mmsystem.h>
// C RunTime �w�b�_�[ �t�@�C��
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
// C++ �w�b�_�[ �t�@�C��
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
// TODO: �v���O�����ɕK�v�Ȓǉ��w�b�_�[�������ŎQ�Ƃ��Ă��������B

#define DISPLAY_WIDTH	800
#define DISPLAY_HEIGHT	600

#include "d3d.h"
#include "device.h"
#include "vertex.h"

#define WM_RENDER	WM_USER
