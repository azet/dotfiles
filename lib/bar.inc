BAR_VERSION=1.4
bar_cat()
{
test -z "${BAR_WIDTH}" && test -n "${COLUMNS}" && BAR_WIDTH=${COLUMNS}
( expr "${BAR_WIDTH}" + 0 >/dev/null 2>&1 ) || BAR_WIDTH=0
BAR_WIDTH=`expr ${BAR_WIDTH} + 0` || BAR_WIDTH=0
test "x${BAR_WIDTH}" = x0 && BAR_WIDTH=76
test -n "${BAR_BS}" || BAR_BS=1048567
test -n "${BAR_PERC}" || BAR_PERC=1
test -n "${BAR_ETA}" || BAR_ETA=1
test -n "${BAR_TRACE_WIDTH}" || BAR_TRACE_WIDTH=10
test -n "${BAR_CMD}" || BAR_CMD=cat
test -n "${BAR_L}"  || BAR_L='['
test -n "${BAR_R}"  || BAR_R=']'
test -n "${BAR_C0}" || BAR_C0='.'
test -n "${BAR_C1}" || BAR_C1='='
test -n "${BAR_OK}" || BAR_OK=1
BAR_WIDTH=`expr ${BAR_WIDTH} - 3`
bar_trace=''
if test "x${BAR_TRACE}" = x1
then
BAR_WIDTH=`expr ${BAR_WIDTH} - ${BAR_TRACE_WIDTH}`
bar_lauf=${BAR_TRACE_WIDTH}
bar_t_space=''
bar_t_dot=''
while test "${bar_lauf}" -gt 1
do
bar_t_space="${bar_t_space} "
bar_t_dot="${bar_t_dot}."
bar_lauf=`expr ${bar_lauf} - 1`
done
bar_trace="${bar_t_space} "
fi
bar_eta=''
BAR_GET_TIME='echo'
( expr 1 + ${SECONDS} >/dev/null 2>&1 ) || BAR_ETA=0
if test "x${BAR_ETA}" = x1
then
BAR_GET_TIME='( echo ${SECONDS} )'
BAR_WIDTH=`expr ${BAR_WIDTH} - 6`
bar_eta='--:-- '
fi
bar_perc=''
if test "x${BAR_PERC}" = x1
then
BAR_WIDTH=`expr ${BAR_WIDTH} - 5`
bar_perc='  0% '
fi
BAR_GET_SIZE='( ls -l "${BAR_DIR}${bar_file}${BAR_EXT}" | sed "s@  *@ @g" | cut -d " " -f 5 ) 2>/dev/null'
( ( echo a                   ) >/dev/null 2>&1 ) || BAR_OK=0
( ( echo a | dd bs=2 count=2 ) >/dev/null 2>&1 ) || BAR_OK=0
( ( echo a | grep a          ) >/dev/null 2>&1 ) || BAR_OK=0
( ( echo a | sed 's@  *@ @g' ) >/dev/null 2>&1 ) || BAR_OK=0
( ( echo a | cut -d ' ' -f 1 ) >/dev/null 2>&1 ) || BAR_OK=0
test "${BAR_WIDTH}" -ge 4 || BAR_OK=0
BAR_ECHO='echo'
BAR_E_C1=''
BAR_E_C2=''
BAR_E_NL='echo'
if echo -n abc >/dev/null 2>&1
then
BAR_E_C1='-n'
fi
if ( ( ${BAR_ECHO} "${BAR_E_C1}" abc ; echo 1,2,3 ) | grep n ) >/dev/null 2>&1
then
if ( ( ${BAR_ECHO} 'xyz\c' ; echo 1,2,3 ) | grep c ) >/dev/null 2>&1
then
if ( ( printf 'ab%s' c ; echo 1,2,3 ) | grep abc ) >/dev/null 2>&1
then
BAR_ECHO='printf'
BAR_E_C1='%s'
else
BAR_ECHO=':'
BAR_E_C1=''
BAR_E_NL=':'
BAR_OK=0
fi
else
BAR_E_C1=''
BAR_E_C2='\c'
fi
fi
bar_shown=0
if test "${BAR_OK}" = 1
then
bar_lauf=0
bar_graph=''
while test `expr ${bar_lauf} + 5` -le "${BAR_WIDTH}"
do
bar_graph="${bar_graph}${BAR_C0}${BAR_C0}${BAR_C0}${BAR_C0}${BAR_C0}"
bar_lauf=`expr ${bar_lauf} + 5`
done
while test "${bar_lauf}" -lt "${BAR_WIDTH}"
do
bar_graph="${bar_graph}${BAR_C0}"
bar_lauf=`expr ${bar_lauf} + 1`
done
${BAR_ECHO} "${BAR_E_C1}" "${bar_trace}${bar_eta}${bar_perc}${BAR_L}${bar_graph}${BAR_R}${BAR_E_C2}" 1>&2
bar_shown=1
fi
( ( test 1999999998 = `expr 999999999 + 999999999` ) >/dev/null 2>&1 ) || BAR_OK=0
bar_large_num="........."
bar_div=""
bar_numsuff=""
bar_size=0
if test -n "${BAR_SIZE}"
then
bar_size=${BAR_SIZE}
while expr "${bar_size}" : "${bar_large_num}" >/dev/null 2>&1
do
bar_div="${bar_div}."
bar_numsuff="${bar_numsuff}0"
bar_size=`expr "${bar_size}" : '\(.*\).$'`
done
BAR_GET_SIZE="echo '${BAR_SIZE}'"
else
for bar_file
do
bar_size1=0
if test -f "${BAR_DIR}${bar_file}${BAR_EXT}"
then
bar_size1=`eval "${BAR_GET_SIZE}"`
if test -n "${bar_div}"
then
bar_size1=`expr "${bar_size1}" : '\(.*\)'${bar_div}'$'` || bar_size1=0
fi
while expr "${bar_size1}" : "${bar_large_num}" >/dev/null 2>&1
do
bar_div="${bar_div}."
bar_numsuff="${bar_numsuff}0"
bar_size1=`expr "${bar_size1}" : '\(.*\).$'`
bar_size=`expr "${bar_size}" : '\(.*\).$'` || bar_size=0
done
if test -n "${bar_div}"
then
bar_size1=`expr "${bar_size1}" + 1`
fi
bar_size=`expr ${bar_size} + ${bar_size1}`
while expr "${bar_size}" : "${bar_large_num}" >/dev/null 2>&1
do
bar_div="${bar_div}."
bar_numsuff="${bar_numsuff}0"
bar_size=`expr "${bar_size}" : '\(.*\).$'`
done
else
BAR_OK=0
fi
done
fi
bar_quad=`expr ${BAR_WIDTH} '*' ${BAR_WIDTH}`
test "${bar_size}" -gt "${bar_quad}" || BAR_OK=0
if test "${BAR_OK}" = 0
then
for bar_file
do
if test "${bar_file}" = "/dev/stdin"
then
eval "${BAR_CMD}"
else
eval "${BAR_CMD}" < "${BAR_DIR}${bar_file}${BAR_EXT}"
fi
done
else
bar_want_bps=`expr ${bar_size} + ${BAR_WIDTH}`
bar_want_bps=`expr ${bar_want_bps} - 1`
bar_want_bps=`expr ${bar_want_bps} / ${BAR_WIDTH}`
bar_count=1
if test "${bar_want_bps}" -gt "${BAR_BS}"
then
bar_count=`expr ${bar_want_bps} + ${BAR_BS}`
bar_count=`expr ${bar_count} - 1`
bar_count=`expr ${bar_count} / ${BAR_BS}`
fi
bar_wc=`expr ${BAR_WIDTH} '*' ${bar_count}`
bar_bs=`expr ${bar_size} + ${bar_wc}`
bar_bs=`expr ${bar_bs} - 1`
bar_bs=`expr ${bar_bs} / ${bar_wc}`
bar_bps=`expr ${bar_bs} '*' ${bar_count}`
bar_bph=`expr ${bar_size} + 99`
bar_bph=`expr ${bar_bph} / 100`
bar_pos=0
bar_graph="${BAR_L}"
bar_cur_char=0
bar_t0=`eval "${BAR_GET_TIME}" 2>/dev/null` || bar_t0=0
for bar_file
do
if test "x${BAR_TRACE}" = x1
then
bar_trace=`expr "${bar_file}" : '.*/\([^/][^/]*\)$'` || bar_trace="${bar_file}"
bar_trace=`expr "${bar_trace}${bar_t_space}" : '\('${bar_t_dot}'\)'`
bar_trace="${bar_trace} "
fi
bar_char=`expr ${bar_pos} / ${bar_want_bps}` || bar_char=0
while test "${bar_char}" -gt `expr ${bar_cur_char} + 4`
do
bar_graph="${bar_graph}${BAR_C1}${BAR_C1}${BAR_C1}${BAR_C1}${BAR_C1}"
bar_cur_char=`expr ${bar_cur_char} + 5`
done
while test "${bar_char}" -gt "${bar_cur_char}"
do
bar_graph="${bar_graph}${BAR_C1}"
bar_cur_char=`expr ${bar_cur_char} + 1`
done
bar_size1=`eval "${BAR_GET_SIZE}" 2>/dev/null` || bar_size1=0
if test -n "${bar_div}"
then
bar_size1=`expr "${bar_size1}" : '\(.*\)'${bar_div}'$'` || bar_size1=0
bar_size1=`expr "${bar_size1}" + 1`
fi
bar_total=0
(
exec 6>&1
exec 5<"${BAR_DIR}${bar_file}${BAR_EXT}"
while test "${bar_total}" -lt "${bar_size1}"
do
dd bs="${bar_bs}" count="${bar_count}${bar_numsuff}" <&5 >&6 2>/dev/null
bar_total=`expr ${bar_total} + ${bar_bps}`
if test "${bar_total}" -gt "${bar_size1}"
then
bar_total="${bar_size1}"
fi
bar_pos1=`expr ${bar_pos} + ${bar_total}`
bar_proz=`expr ${bar_pos1} / ${bar_bph}` || bar_proz=0
if test "x${BAR_PERC}" = x1
then
bar_perc="  ${bar_proz}% "
bar_perc=`expr "${bar_perc}" : '.*\(.....\)$'`
fi
if test "x${BAR_ETA}" = x1
then
bar_diff=`eval "${BAR_GET_TIME}" 2>/dev/null` || bar_diff=0
bar_diff=`expr ${bar_diff} - ${bar_t0} 2>/dev/null` || bar_diff=0
bar_100p=`expr 100 - ${bar_proz}` || bar_100p=0
bar_diff=`expr ${bar_diff} '*' ${bar_100p}` || bar_diff=0
bar_diff=`expr ${bar_diff} + ${bar_proz}` || bar_diff=0
bar_diff=`expr ${bar_diff} - 1` || bar_diff=0
bar_diff=`expr ${bar_diff} / ${bar_proz} 2>/dev/null` || bar_diff=0
if test "${bar_diff}" -gt 0
then
bar_t_unit=":"
if test "${bar_diff}" -gt 2700
then
bar_t_uni="h"
bar_diff=`expr ${bar_diff} / 60`
fi
bar_diff_h=`expr ${bar_diff} / 60` || bar_diff_h=0
if test "${bar_diff_h}" -gt 99
then
bar_eta="     ${bar_diff_h}${bar_t_unit} "
else
bar_diff_hi=`expr ${bar_diff_h} '*' 60` || bar_diff_hi=0
bar_diff=`expr ${bar_diff} - ${bar_diff_hi}` || bar_diff=0
bar_diff=`expr "00${bar_diff}" : '.*\(..\)$'`
bar_eta="     ${bar_diff_h}${bar_t_unit}${bar_diff} "
fi
bar_eta=`expr "${bar_eta}" : '.*\(......\)$'`
fi
fi
bar_char=`expr ${bar_pos1} / ${bar_want_bps}` || bar_char=0
while test "${bar_char}" -gt "${bar_cur_char}"
do
bar_graph="${bar_graph}${BAR_C1}"
${BAR_ECHO} "${BAR_E_C1}" "${bar_trace}${bar_eta}${bar_perc}${bar_graph}${BAR_E_C2}" 1>&2
bar_cur_char=`expr ${bar_cur_char} + 1`
done
done
) | eval "${BAR_CMD}"
bar_pos=`expr ${bar_pos} + ${bar_size1}`
done
fi
if test "${bar_shown}" = 1
then
test "x${BAR_TRACE}" = x1 && bar_trace="${bar_t_space} "
test "x${BAR_ETA}" = x1   && bar_eta='      '
if test "x${BAR_CLEAR}" = x1
then
test "x${BAR_PERC}" = x1 && bar_perc='     '
bar_lauf=0
bar_graph=''
while test `expr ${bar_lauf} + 5` -le "${BAR_WIDTH}"
do
bar_graph="${bar_graph}     "
bar_lauf=`expr ${bar_lauf} + 5`
done
while test "${bar_lauf}" -lt "${BAR_WIDTH}"
do
bar_graph="${bar_graph} "
bar_lauf=`expr ${bar_lauf} + 1`
done
${BAR_ECHO} "${BAR_E_C1}" "${bar_trace}${bar_eta}${bar_perc} ${bar_graph} ${BAR_E_C2}" 1>&2
else
test "x${BAR_PERC}" = x1 && bar_perc='100% '
bar_lauf=0
bar_graph=''
while test `expr ${bar_lauf} + 5` -le "${BAR_WIDTH}"
do
bar_graph="${bar_graph}${BAR_C1}${BAR_C1}${BAR_C1}${BAR_C1}${BAR_C1}"
bar_lauf=`expr ${bar_lauf} + 5`
done
while test "${bar_lauf}" -lt "${BAR_WIDTH}"
do
bar_graph="${bar_graph}${BAR_C1}"
bar_lauf=`expr ${bar_lauf} + 1`
done
${BAR_ECHO} "${BAR_E_C1}" "${bar_trace}${bar_eta}${bar_perc}${BAR_L}${bar_graph}${BAR_R}${BAR_E_C2}" 1>&2
${BAR_E_NL} 1>&2
fi
fi
}
