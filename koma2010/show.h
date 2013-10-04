#ifndef	SHOW_H
#define	SHOW_H

#include	"function.h"

class Show
{
private:
	IGraphBuilder *lpGraph;
	IMediaControl *lpMediaControl;
	IMediaEventEx *lpEvent;
	IMediaSeeking *lpSeek;
	double speed;
public:
	bool loop;
	Show();
	virtual ~Show();
	virtual bool LoadMp3File(const unsigned short *str);
	virtual void CheckMp3State(void);
	virtual void SetSpeed(double rate)
	{
		speed=rate;
	}
	double GetSpeed(){return speed;}
	IGraphBuilder	*GetGraphBuilder()
	{
		return lpGraph;
	}
	IMediaControl	*GetMediaControl()
	{
		return lpMediaControl;
	}
	IMediaSeeking	*GetMediaSeeking()
	{
		return lpSeek;
	}
};

#endif	SHOW_H