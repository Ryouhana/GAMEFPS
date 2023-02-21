#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

class Effect {

public:
    /// <summary>
 /// エフェクトを有効にする
 /// </summary>
 /// <param name="UpdateFunction">エフェクト実体</param>
 /// <returns>エフェクトのインデックス</returns>
    int Add(std::function<bool(int)> UpdateFunction) {
        EffectList.push_back(UpdateFunction);
        Counter.push_back(0);
        Valid.push_back(true);
        Finished.push_back(false);
        return EffectList.size() - 1;
    }

    /// <summary>
    /// エフェクトの一時停止
    /// </summary>
    /// <param name="index">一時停止するエフェクトのインデックス</param>
    void Pause(int index) {
        if (index >= EffectList.size() || Finished[(int)index]) return;
        Valid[(int)index] = false;
    }

    /// <summary>
    /// 一時停止したエフェクトの再開
    /// </summary>
    /// <param name="index">再開するエフェクトのインデックス</param>
    void Resume(int index) {
        if (index >= EffectList.size() || Finished[(int)index]) return;
        Valid[(int)index] = true;
    }

    /// <summary>
    /// エフェクトの停止
    /// </summary>
    /// <param name="index">停止するエフェクトのインデックス</param>
    void Stop(int index) {
        if (index >= EffectList.size() || Finished[(int)index]) return;
        Valid[(int)index] = false;
        Finished[(int)index] = true;
    }

    /// <summary>
    /// 停止されているエフェクトを一番最初から再開する
    /// </summary>
    /// <param name="index">再開するエフェクトのインデックス</param>
    void Restart(int index) {
        Counter[(int)index] = 0;
        Valid[(int)index] = true;
        Finished[(int)index] = false;
    }

    /// <summary>
    /// <para>エフェクトを処理する</para>
    /// <para>メインループ内で呼ぶ</para>
    /// </summary>
    void Update() {
        if (EffectList.size() == 0) {
            return;
        }

        for (int i = 0; EffectList.size() > i; i++) {
            if (!Valid[i]) {
                continue;
            }
            bool r = EffectList[i](Counter[i]); //trueのときに終了する
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
