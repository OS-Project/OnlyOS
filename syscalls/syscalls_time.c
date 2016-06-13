/*
    * Created by Thibault on 17/01/2016.
*/

int _times(struct tms *buf) {
    int sys_time = kgetTime(); /* Kernel time */

    buf->tms_utime = sys_time;
    buf->tms_stime = sys_time;

    buf->tms_cutime = sys_time;
    buf->tms_cstime = sys_time;
    return sys_time;
}

