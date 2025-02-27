import cv2                  #incluye libreria cv
import numpy as np          #incluye numpy para procesar datos



def Carga_y_comprueba(Lugar_imagen):
    """
    Carga la imagen
    Argumento:
        Lugar_imagen (str):Donde tenemos guardada la imagen
    """
    try:
        img = cv2.imread(Lugar_imagen)  #funcion de cv2 para leer la imagen
        if img is None:                    #comprueba errores
            raise FileNotFoundError(f"Image not found at {Lugar_imagen}")

        cv2.imshow('Imagen', img)           #enseña la imagen
        cv2.waitKey(0)  # Espera a que se pulse una imagen para comprobar la imagen
        cv2.destroyAllWindows()
        return img  # Devuelve la imagen para continuar la funcion
    except FileNotFoundError as e:
        print(f"Error: {e}")
        return None
    except Exception as e:
        print(f"Hemos tenido un error {e}")
        return None


# Uso 
Lugar_imagen = 'resistor.jpg'  # Reemplaza con donde esta la imagen
img = Carga_y_comprueba(Lugar_imagen)



def preprocess_image(img):
    """
    Convierte a grayscale y hace funcion gausiana para reducir el ruido

    Args:
        img : Imagen inicial.
    """
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    blurred = cv2.GaussianBlur(gray, (5, 5), 0) #le pasamos como argumentos los valores necesarios. He usado los valores que encontre en internet
    return blurred          #devuelve la imagen tras aplicar gauss

if img is not None:             #control de errores            
    preprocessed_img = preprocess_image(img)        #llamo a la funcion de preprocesamiento
    cv2.imshow('Imagen inicial', preprocessed_img)  #enseño la foto procesada
    cv2.waitKey(0)  
    cv2.destroyAllWindows()


def aislar_resistor(preprocessed_img, original_img):
    """
    Encuentra el resistor 

    """
    bordes = cv2.Canny(preprocessed_img, 50, 150) #Ajusta los bordes segun sea necesario
    contours, _ = cv2.findContours(bordes, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    if contours:
        largest_contour = max(contours, key=cv2.contourArea)
        x, y, w, h = cv2.boundingRect(largest_contour)
        cropped_resistor = original_img[y:y + h, x:x + w]
        return cropped_resistor
    else:
        print("Error de los contornos")
        return None

if img is not None:
    Resistor_encontrado = aislar_resistor(preprocessed_img, img)
    if Resistor_encontrado is not None:
        cv2.imshow('Cropped Resistor', Resistor_encontrado)     #muestra la imagen
        cv2.waitKey(0)
        cv2.destroyAllWindows()


def detect_bands(cropped_resistor):
    """
    
    """
    hsv = cv2.cvtColor(cropped_resistor, cv2.COLOR_BGR2HSV)

    color_ranges = {
        "brown": ([10, 50, 50], [20, 255, 255]),
        "red": ([0, 100, 100], [10, 255, 255]),
        "orange": ([11, 150, 150], [24, 255, 255]),
        "yellow": ([25, 150, 150], [35, 255, 255]),
        "green": ([36, 50, 50], [70, 255, 255]),
        "blue": ([100, 50, 50], [130, 255, 255]),
        "violet": ([135, 50, 50], [160, 255, 255]),
        "gray": ([0, 0, 40], [180, 40, 100]),
        "white": ([0, 0, 200], [180, 20, 255]),
        "gold": ([20, 100, 100], [30, 255, 255]),
        "silver": ([0, 0, 100], [180, 20, 150])
    }

    band_data = []

    for color, (lower, upper) in color_ranges.items():
        lower = np.array(lower, dtype=np.uint8)
        upper = np.array(upper, dtype=np.uint8)
        mask = cv2.inRange(hsv, lower, upper)
        contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        if contours:
            for contour in contours:
                band_data.append({"contour": contour, "color": color})

    def get_contour_x(band):
        x, _, _, _ = cv2.boundingRect(band["contour"])
        return x

    band_data.sort(key=get_contour_x)

    return band_data

if Resistor_encontrado is not None:
    band_data = detect_bands(Resistor_encontrado)
    img_with_contours = Resistor_encontrado.copy()

    for band in band_data:
        cv2.drawContours(img_with_contours, [band["contour"]], -1, (0, 255, 0), 2)
        print(f"Band Color: {band['color']}") #print the color of the band

    cv2.imshow('Bands Detected', img_with_contours)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    color_codes = {
    "black": {"value": 0, "multiplier": 1},
    "brown": {"value": 1, "multiplier": 10},
    "red": {"value": 2, "multiplier": 100},
    "orange": {"value": 3, "multiplier": 1000},
    "yellow": {"value": 4, "multiplier": 10000},
    "green": {"value": 5, "multiplier": 100000},
    "blue": {"value": 6, "multiplier": 1000000},
    "violet": {"value": 7, "multiplier": 10000000},
    "gray": {"value": 8, "multiplier": 100000000},
    "white": {"value": 9, "multiplier": 1000000000},
    "gold": {"multiplier": 0.1, "tolerance": 5},
    "silver": {"multiplier": 0.01, "tolerance": 10}
}
    

def calculate_resistance(band_data):
    # (function code as defined previously)
    if not band_data:
       return None, None

    num_bands = len(band_data)
    resistance = 0.0
    tolerance = None

    if num_bands == 4:
        # 4-band resistor
        digit1 = color_codes[band_data[0]["color"]]["value"]
        digit2 = color_codes[band_data[1]["color"]]["value"]
        multiplier = color_codes[band_data[2]["color"]]["multiplier"]
        tolerance = color_codes[band_data[3]["color"]].get("tolerance")

        resistance = (digit1 * 10 + digit2) * multiplier

    elif num_bands == 5:
         # 5-band resistor
        digit1 = color_codes[band_data[0]["color"]]["value"]
        digit2 = color_codes[band_data[1]["color"]]["value"]
        digit3 = color_codes[band_data[2]["color"]]["value"]
        multiplier = color_codes[band_data[3]["color"]]["multiplier"]
        tolerance = color_codes[band_data[4]["color"]].get("tolerance")

        resistance = (digit1 * 100 + digit2 * 10 + digit3) * multiplier

    else:
        print("Unsupported number of bands.")
        return None, None

    return resistance, tolerance

if Resistor_encontrado is not None:
    band_data = detect_bands(Resistor_encontrado)

    if band_data: #check if band_data is not empty.
        resistance, tolerance = Resistor_encontrado(band_data)

        if resistance is not None:
            if tolerance is not None:
                print(f"Resistance: {resistance} ohms ±{tolerance}%")
            else:
                print(f"Resistance: {resistance} ohms")
        else:
            print("No se encontro resistencia")
    else:
        print("No se han encontrado bandas")



# color_codes, detect_bands, and calculate_resistance (as defined previously)

def process_frame(frame):
    """
    
    """
    try:
        # 1. Isolate Resistor
        preprocessed_frame = preprocess_image(frame)
        cropped_resistor = isolate_resistor(preprocessed_frame, frame)

        if cropped_resistor is not None:
            # 2. Detect Bands
            band_data = detect_bands(cropped_resistor)

            if band_data:
                # 3. Calculate Resistance
                resistance, tolerance = calculate_resistance(band_data)

                # 4. Draw Contours and Display Resistance
                img_with_contours = cropped_resistor.copy()
                for band in band_data:
                    cv2.drawContours(img_with_contours, [band["contour"]], -1, (0, 255, 0), 2)

                if resistance is not None:
                    if tolerance is not None:
                        text = f"Resistance: {resistance} ohms ±{tolerance}%"
                    else:
                        text = f"Resistance: {resistance} ohms"
                    cv2.putText(img_with_contours, text, (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
                else:
                    cv2.putText(img_with_contours, "Could not calculate resistance.", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)

                # Replace the original frame resistor area with the processed data.
                x, y, w, h = cv2.boundingRect(max([band["contour"] for band in band_data], key=cv2.contourArea))
                frame[y:y + h, x:x + w] = img_with_contours

    except Exception as e:
        print(f"Error processing frame: {e}")

    return frame

def preprocess_image(img):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    blurred = cv2.GaussianBlur(gray, (5, 5), 0)
    return blurred

def isolate_resistor(preprocessed_img, original_img):
    edges = cv2.Canny(preprocessed_img, 50, 150)
    contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    if contours:
        largest_contour = max(contours, key=cv2.contourArea)
        x, y, w, h = cv2.boundingRect(largest_contour)
        cropped_resistor = original_img[y:y + h, x:x + w]
        return cropped_resistor
    else:
        return None

# Main Loop
cap = cv2.VideoCapture(0)  # 0 for default camera
if not cap.isOpened():
    print("Error: Could not open camera.")
    exit()

while True:
    ret, frame = cap.read()
    if not ret:
        print("Error: Could not read frame.")
        break

    processed_frame = process_frame(frame)

    cv2.imshow('Resistor Reader', processed_frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()


