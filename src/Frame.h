enum FType {
    Normal,
    Final
};

typedef struct {
    int _pinNums[3];
    FType _type;
} Frame;


//あまりいいとは思わないがこういう実装例も
int Frame_Score(const Frame* frame, const Frame* nextFrame, const Frame* nextNextFrame)
{
    if (isStrike(frame))
    {
        return 10 + scoreBonusForStrike(nextFrame, nextNextFrame);
    }
    else if (isSpare(frame))
    {
        return 10 + scoreBonusForSpare(nextFrame);
    }

    return sumOfPins(frame);
}