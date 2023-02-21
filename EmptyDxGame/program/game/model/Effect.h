#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

class Effect {

public:
    /// <summary>
 /// �G�t�F�N�g��L���ɂ���
 /// </summary>
 /// <param name="UpdateFunction">�G�t�F�N�g����</param>
 /// <returns>�G�t�F�N�g�̃C���f�b�N�X</returns>
    int Add(std::function<bool(int)> UpdateFunction) {
        EffectList.push_back(UpdateFunction);
        Counter.push_back(0);
        Valid.push_back(true);
        Finished.push_back(false);
        return EffectList.size() - 1;
    }

    /// <summary>
    /// �G�t�F�N�g�̈ꎞ��~
    /// </summary>
    /// <param name="index">�ꎞ��~����G�t�F�N�g�̃C���f�b�N�X</param>
    void Pause(int index) {
        if (index >= EffectList.size() || Finished[(int)index]) return;
        Valid[(int)index] = false;
    }

    /// <summary>
    /// �ꎞ��~�����G�t�F�N�g�̍ĊJ
    /// </summary>
    /// <param name="index">�ĊJ����G�t�F�N�g�̃C���f�b�N�X</param>
    void Resume(int index) {
        if (index >= EffectList.size() || Finished[(int)index]) return;
        Valid[(int)index] = true;
    }

    /// <summary>
    /// �G�t�F�N�g�̒�~
    /// </summary>
    /// <param name="index">��~����G�t�F�N�g�̃C���f�b�N�X</param>
    void Stop(int index) {
        if (index >= EffectList.size() || Finished[(int)index]) return;
        Valid[(int)index] = false;
        Finished[(int)index] = true;
    }

    /// <summary>
    /// ��~����Ă���G�t�F�N�g����ԍŏ�����ĊJ����
    /// </summary>
    /// <param name="index">�ĊJ����G�t�F�N�g�̃C���f�b�N�X</param>
    void Restart(int index) {
        Counter[(int)index] = 0;
        Valid[(int)index] = true;
        Finished[(int)index] = false;
    }

    /// <summary>
    /// <para>�G�t�F�N�g����������</para>
    /// <para>���C�����[�v���ŌĂ�</para>
    /// </summary>
    void Update() {
        if (EffectList.size() == 0) {
            return;
        }

        for (int i = 0; EffectList.size() > i; i++) {
            if (!Valid[i]) {
                continue;
            }
            bool r = EffectList[i](Counter[i]); //true�̂Ƃ��ɏI������
            Counter[i]++;
            if (r) {
                Finished[i] = true;
                Valid[i] = false;
            }
        }
    }
private:
    std::vector<std::function<bool(int)>> EffectList;
    std::vector<bool> Valid, Finished;
    std::vector<int> Counter;
};
