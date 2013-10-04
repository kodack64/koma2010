#include "dx8.h"

void CDirectX::MoveMatrix(LPTLVERTEX v, float x, float y, float z)
{
    D3DXMATRIX PosMatrix, MoveMatrix;
    int i;

    // 行列の初期化（単位行列生成）
    D3DXMatrixIdentity(&PosMatrix);
    D3DXMatrixIdentity(&MoveMatrix);

    // 移動量設定
    D3DXMatrixTranslation(&MoveMatrix, x, y, z);

    // 移動処理
    for ( i=0 ; i<4 ; i++ ) {
        // 現在の頂点座標を格納
        D3DXMatrixTranslation(&PosMatrix, v[i].x, v[i].y, v[i].z);
        // 演算
        PosMatrix *= MoveMatrix;
        // 結果を戻す
        v[i].x = PosMatrix._41;
        v[i].y = PosMatrix._42;
        v[i].z = PosMatrix._43;
    }

}

void CDirectX::ZoomMatrix(LPTLVERTEX v, float x, float y, float z)
{
    D3DXMATRIX PosMatrix, ZoomMatrix;
    float x1, y1;
    int i;

    // ポリゴンの中心を求め、原点へ移動させる
    x1 = (v[2].x - v[0].x) / 2.0f + v[0].x;
    y1 = (v[3].y - v[1].y) / 2.0f + v[1].y;
    MoveMatrix(v, -x1, -y1, 0.0f);

    // 行列の初期化（単位行列生成）
    D3DXMatrixIdentity(&PosMatrix);
    D3DXMatrixIdentity(&ZoomMatrix);

    // 拡大行列に倍率を設定
    D3DXMatrixScaling(&ZoomMatrix, x, y, z);

    // 拡大／縮小処理
    for ( i=0 ; i<4 ; i++ ) {
        // 現在の頂点座標を格納
        D3DXMatrixTranslation(&PosMatrix, v[i].x, v[i].y, v[i].z);
        // 演算
        PosMatrix *= ZoomMatrix;
        // 結果を戻す
        v[i].x = PosMatrix._41;
        v[i].y = PosMatrix._42;
        v[i].z = PosMatrix._43;
    }

    // ポリゴンを元の位置へ戻す
    MoveMatrix(v, x1, y1, 0.0f);

}

void CDirectX::RotateMatrix(LPTLVERTEX v, int Rotate)
{
    float PAD = 3.141592f / 180.0f; // ラジアンの初期化
    D3DXMATRIX PosMatrix, RotateMatrix;
    float x1, y1;
    int i;

    // ポリゴンの中心を求め、原点へ移動させる
    x1 = (v[2].x - v[0].x) / 2.0f + v[0].x;
    y1 = (v[3].y - v[1].y) / 2.0f + v[1].y;
    MoveMatrix(v, -x1, -y1, 0.0f);

    // 行列の初期化（単位行列生成）
    D3DXMatrixIdentity(&PosMatrix);
    D3DXMatrixIdentity(&RotateMatrix);

    // 回転行列に角度を設定
    D3DXMatrixRotationZ(&RotateMatrix, (float)Rotate * PAD);

    // 回転処理
    for ( i=0 ; i<4 ; i++ ) {
        // 現在の頂点座標を格納
        D3DXMatrixTranslation(&PosMatrix, v[i].x, v[i].y, v[i].z);
        // 演算
        PosMatrix *= RotateMatrix;
        // 結果を戻す
        v[i].x = PosMatrix._41;
        v[i].y = PosMatrix._42;
        v[i].z = PosMatrix._43;
    }

    // ポリゴンを元の位置へ戻す
    MoveMatrix(v, x1, y1, 0.0f);

}
