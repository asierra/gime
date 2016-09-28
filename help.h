/*
 * This file is part of GIME, a System to track storms interactively
 * and to do basic meteorological image processing.
 *
 * GIME is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Copyright (c) 2002-2018  Alejandro Aguilar Sierra (asierra@unam.mx)
 * Centro de Ciencias de la Atmosfera, UNAM         
 */

const char *help_string = "<h2>GIME - Sistema de rastreo de tormentas</h2> "
" "
"GIME es un programa para analizar y rastrear tormentas "
"en secuencias de imágenes o mapas meteorológicos. "
"Funciona con el siguiente procedimiento: "
" "
"<ol> "
"<li>Si la sesión es nueva, cargue una secuencia de "
"imágenes. De lo contrario, cargue una sesión previa,</li> "
"<li>Asignarle una fecha a cada imagen. </li> "
"<li>Para seleccionar cualquier imagen, usar el ratón o las "
"teclas de flechas verticales.</li> "
"<li>Para insertar una nueva trayectoria, oprimir el botón \"+\" "
"del panel inferior.</li> "
"<li>Para capturar una posición, colocar el cursor del ratón "
"y dar doble click.<li> "
"</ol> "
" "
"<p> "
"Hay dos maneras de asignar fechas a las imágenes. "
"</p> "
" "
"<ol> "
"<li>Manualmente, debajo del panel de imágenes, modificar "
"la fecha y hora. Oprimir \"Cambiar Fecha\" y la nueva fecha "
"será asignada a la imagen actualmente seleccionada.</li> "
"<li>Una manera más eficiente para un conjunto grande de "
"imágenes es usar el nombre del archivo de la imagen, en el "
"menú <tt>edit->Extrae fechas de nombre</tt>. Sólo hay que "
"indicar con letras, las partes que corresponden a la fecha "
"y la hora (hora, minutos y segundos) y se asignará fecha a "
"todas las imágenes. "
"</li> "
"</ol> "
" "
"<p> "
"Para visualizar fechas, oprimir el botón \"A\" y especificar "
"los campos de fecha y hora que desea, si es que el que se "
"usa por omisión no es apropiado. <br/>Al incrementar el contador "
"en los botones de formato de fecha, aumenta el espacio entre "
"posiciones fechadas. Si se desea poner o quitar fecha en la "
"posición correspondiente a la imagen actual, oprimir la letra <b>F</b>. "
"</p> "
" "
" "
;