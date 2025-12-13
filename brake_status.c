
const char* brake_status(int pos, int brake_switch){

    if(pos < 0  || pos > 100)
    {
        return "brake_invalid";
    }
    
    else if((pos == 0) && (brake_switch == 0))
    {
        return "released";
    }

    else if(((pos == 0) && (brake_switch == 1)) || ((pos > 0) && (brake_switch == 0)))
    {
        return "inconclusive";
    }

    else if((pos > 0  && pos <= 30) && (brake_switch == 1))
    {
        return "brake_light";
    }

    else if((pos > 30) && (brake_switch == 1))
    {
        return "brake_hard";
    }

    return "brake_invalid";
}