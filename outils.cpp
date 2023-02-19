/*****************************************************************
Auteurs : ASSE Romain FERRE Cedric
Date : 21 novembre 2022
Fichier : outils.cxx
But : définir les actions seuillage et différence
*****************************************************************/

#include <stdlib.h>
#include <string.h>
#include "outils.h"
#include "image.h"

static unsigned int get_nb_white_px(t_Image *img);
static void fill_of_black(t_Image *img);

/**
 * Permet de remplir une strucutre t_Image de noir
 * img   Pointeur sur l'image
*/
static void fill_of_black(t_Image *img)
{
    for (int i = 0; i < img->w; i++)
    {
        for (int j = 0; j < img->h; j++)
        {
            img->im[i][j] = NOIR;
        }
    }
}

/**
 * Permet de récupérer le nombre de pixels blanc d'une structure t_Image
 * img   Pointeur sur l'image
 * retourne le nombre de pixel blanc
*/
static unsigned int get_nb_white_px(t_Image *img)
{
    unsigned int count = 0;

    for (int k = 0; k < img->h; k++)
    {
        for (int l = 0; l < img->w; l++)
        {
            if (img->im[k][l] == BLANC)
                count++;
        }
    }

    return count;
}

/**
 * Permet d'effectuer une fonction de seuillage sur une image de type t_Image
 * seuil   Valeur de seuil
 * t_Image Pointeur sur l'image
*/
void outils_seuillage(unsigned int seuil, t_Image *img)
{
    unsigned int imValue;

    for (int i = 0; i < img->w; i++)
    {
        for (int j = 0; j < img->h; j++)
        {
            imValue = img->im[i][j];
            img->im[i][j] = (imValue < seuil) ? NOIR : BLANC;
        }
    }
}

/**
 * Permet d'effectuer la différence entre deux images
 * img1   Pointeur sur l'image n°1
 * img2   Pointeur sur l'image n°2
 * img3   Difference absolue entre im1 et img2
*/
void outils_diference(t_Image *img1, t_Image *img2, t_Image *img3)
{
    int imValue;

    memset(img3, 0, sizeof(t_Image));

    img3->w = (img1->w > img2->w) ? img1->w : img2->w;
    img3->h = (img1->h > img2->h) ? img1->h : img2->h;

    for (int i = 0; i < img3->w; i++)
    {
        for (int j = 0; j < img3->h; j++)
        {
            imValue = img1->im[i][j] - img2->im[i][j];
            img3->im[i][j] = abs(imValue);
        }
    }
}

/**
 * Permet d'effectuer la dialation entre deux images
 * img1   Pointeur sur l'element structurant
 * img2   Pointeur sur l'image
 * img3   Résultat de la dialation de l'image
*/
int outils_dilatation(t_Image *elem_struct, t_Image *img, t_Image *img_dil)
{
    int x_center = 0, y_center = 0;

    //La longueur et largeur impaire
    if ((elem_struct->h % 3 != 0) || (elem_struct->w % 3 != 0))
        return -1;

    //On prépare l'image de sortie
    img_dil->h = img->h;
    img_dil->w = img->w;
    fill_of_black(img_dil);

    //on récupere le nombre de pixels blanc de notre element struct
    x_center = (elem_struct->w / 2);
    y_center = (elem_struct->h / 2);

    for (int i = y_center; i < (img->h - y_center); i++)
    {
        for (int j = x_center; j < (img->w - x_center); j++)
        {
            for (int k = 0; k < elem_struct->h; k++)
            {
                for (int l = 0; l < elem_struct->w; l++)
                {
                    if (elem_struct->im[k][l] == BLANC)
                    {
                        //On calque le milieu du pattern sur le point courant
                        if (img->im[i - x_center + k][j - y_center + l] == BLANC)
                        {
                            img_dil->im[i][j] = BLANC;
                            break;
                        }
                    }
                }
            }
        }
    }

    return 0;
}

/**
 * Permet d'effectuer la dialation entre deux images
 * img1   Pointeur sur l'element structurant
 * img2   Pointeur sur l'image
 * img3   Résultat de la dialation de l'image
*/
int outils_erosion(t_Image *elem_struct, t_Image *img, t_Image *img_err)
{
    int x_center = 0, y_center = 0;
    unsigned int nb_px_elem = 0, cout_white_px = 0;;

    //La longueur et largeur impaire
    if ((elem_struct->h % 3 != 0) || (elem_struct->w % 3 != 0))
        return -1;

    //On prépare l'image de sortie
    img_err->h = img->h;
    img_err->w = img->w;
    fill_of_black(img_err);

    //on récupere le nombre de pixels blanc de notre element struct
    nb_px_elem = get_nb_white_px(elem_struct);

    //si l'element n'est pas carré...
    x_center = (elem_struct->w / 2);
    y_center = (elem_struct->h / 2);

    for (int i = y_center; i < (img->h - y_center); i++)
    {
        for (int j = x_center; j < (img->w - x_center); j++)
        {
            //Rénitialisation de la variable de comptage
            cout_white_px = 0;
            for (int k = 0; k < elem_struct->h; k++)
            {
                for (int l = 0; l < elem_struct->w; l++)
                {
                    if (elem_struct->im[k][l] == BLANC)
                    {
                        //On calque le milieu du pattern sur le point courant
                        if (img->im[i - x_center + k][j - y_center + l] == BLANC)
                        {
                            cout_white_px++;
                            //Le pattern recouvre l'image
                            if (cout_white_px == nb_px_elem)
                            {
                                img_err->im[i][j] = BLANC;
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}

/**
 * Permet d'effectuer une ouverture sur une image
 * elem_struct   Pointeur sur l'element structurant
 * img           Pointeur sur l'image
 * img_ouv       Résultat de l'opération d'ouverture
*/
void outils_ouverture(t_Image *elem_struct, t_Image *img, t_Image *img_ouv)
{
    t_Image *tmp = NULL;
    tmp = new(t_Image);

    //Opération d'érosion + dilatation
    outils_erosion(elem_struct, img, tmp);
    outils_dilatation(elem_struct, tmp, img_ouv);
}


/**
 * Permet d'effectuer une fermeture sur une image
 * elem_struct   Pointeur sur l'element structurant
 * img           Pointeur sur l'image
 * img_ouv       Résultat de l'opération d'ouverture
*/
void outils_fermeture(t_Image *elem_struct, t_Image *img, t_Image *img_fer)
{
    t_Image *tmp = NULL;
    tmp = new(t_Image);

    //Opération d'érosion + dilatation
    outils_dilatation(elem_struct, img, tmp);
    outils_erosion(elem_struct, tmp, img_fer);
}