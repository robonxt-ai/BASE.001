/*  ------------------------------------------------------------------------------------------------------
    [6/??/2020] mapFloat > like map(), but supports floats
    ------------------------------------------------------------------------------------------------------*/

int mapFloat (float Angle, float min_ms, float max_ms, float min_angle, float max_angle)
{
    return (((max_ms - min_ms) / (max_angle - min_angle)) * (Angle - min_angle)) + min_ms;
}
