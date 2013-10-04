#include "dx8.h"

void CDirectX::MoveMatrix(LPTLVERTEX v, float x, float y, float z)
{
    D3DXMATRIX PosMatrix, MoveMatrix;
    int i;

    // �s��̏������i�P�ʍs�񐶐��j
    D3DXMatrixIdentity(&PosMatrix);
    D3DXMatrixIdentity(&MoveMatrix);

    // �ړ��ʐݒ�
    D3DXMatrixTranslation(&MoveMatrix, x, y, z);

    // �ړ�����
    for ( i=0 ; i<4 ; i++ ) {
        // ���݂̒��_���W���i�[
        D3DXMatrixTranslation(&PosMatrix, v[i].x, v[i].y, v[i].z);
        // ���Z
        PosMatrix *= MoveMatrix;
        // ���ʂ�߂�
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

    // �|���S���̒��S�����߁A���_�ֈړ�������
    x1 = (v[2].x - v[0].x) / 2.0f + v[0].x;
    y1 = (v[3].y - v[1].y) / 2.0f + v[1].y;
    MoveMatrix(v, -x1, -y1, 0.0f);

    // �s��̏������i�P�ʍs�񐶐��j
    D3DXMatrixIdentity(&PosMatrix);
    D3DXMatrixIdentity(&ZoomMatrix);

    // �g��s��ɔ{����ݒ�
    D3DXMatrixScaling(&ZoomMatrix, x, y, z);

    // �g��^�k������
    for ( i=0 ; i<4 ; i++ ) {
        // ���݂̒��_���W���i�[
        D3DXMatrixTranslation(&PosMatrix, v[i].x, v[i].y, v[i].z);
        // ���Z
        PosMatrix *= ZoomMatrix;
        // ���ʂ�߂�
        v[i].x = PosMatrix._41;
        v[i].y = PosMatrix._42;
        v[i].z = PosMatrix._43;
    }

    // �|���S�������̈ʒu�֖߂�
    MoveMatrix(v, x1, y1, 0.0f);

}

void CDirectX::RotateMatrix(LPTLVERTEX v, int Rotate)
{
    float PAD = 3.141592f / 180.0f; // ���W�A���̏�����
    D3DXMATRIX PosMatrix, RotateMatrix;
    float x1, y1;
    int i;

    // �|���S���̒��S�����߁A���_�ֈړ�������
    x1 = (v[2].x - v[0].x) / 2.0f + v[0].x;
    y1 = (v[3].y - v[1].y) / 2.0f + v[1].y;
    MoveMatrix(v, -x1, -y1, 0.0f);

    // �s��̏������i�P�ʍs�񐶐��j
    D3DXMatrixIdentity(&PosMatrix);
    D3DXMatrixIdentity(&RotateMatrix);

    // ��]�s��Ɋp�x��ݒ�
    D3DXMatrixRotationZ(&RotateMatrix, (float)Rotate * PAD);

    // ��]����
    for ( i=0 ; i<4 ; i++ ) {
        // ���݂̒��_���W���i�[
        D3DXMatrixTranslation(&PosMatrix, v[i].x, v[i].y, v[i].z);
        // ���Z
        PosMatrix *= RotateMatrix;
        // ���ʂ�߂�
        v[i].x = PosMatrix._41;
        v[i].y = PosMatrix._42;
        v[i].z = PosMatrix._43;
    }

    // �|���S�������̈ʒu�֖߂�
    MoveMatrix(v, x1, y1, 0.0f);

}
