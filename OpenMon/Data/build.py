#!/bin/bash/python3

"""
Import csv files for the base data into a sqlite3 database.abs
"""

import sys
import sqlite3
import csv

def main():
    """
    Entry function.
    """

    conn = sqlite3.connect('openmon.sqlite')
    cursor = conn.cursor()

    mon(conn, cursor)
    types(conn, cursor)
    stats(conn, cursor)

    conn.close()


def mon(conn, cursor):
    """
    Defines the mon, mon_stats, mon_types tables and loads the default data.
    """

    cursor.execute('''
        CREATE TABLE mon 
           (id INT,
            identifier TEXT,
            species_id INT,
            height INT,
            weight INT,
            base_experience INT,
            is_default INT);
    ''')
    cursor.execute('''
        CREATE TABLE mon_stats 
           (pokemon_id INT,
            stat_id INT,
            base_stat INT,
            effort INT);
    ''')
    cursor.execute('''
        CREATE TABLE mon_types 
           (pokemon_id INT,
            type_id INT,
            slot INT);
    ''')

    with open('pokemon.csv', 'r') as infile:
        reader = csv.DictReader(infile)
        to_db = [(row['id'], row['identifier'], row['species_id'],
                  row['height'], row['weight'], row['base_experience'],
                  row['is_default']) for row in reader]

    cursor.executemany('''
        INSERT INTO mon
           (id,
            identifier,
            species_id,
            height,
            weight,
            base_experience,
            is_default)
        VALUES (?, ?, ?, ?, ?, ?, ?);
    ''', to_db)
    conn.commit()

    with open('pokemon_stats.csv', 'r') as infile:
        reader = csv.DictReader(infile)
        to_db = [(row['pokemon_id'], row['stat_id'], row['base_stat'],
                  row['effort']) for row in reader]

    cursor.executemany('''
        INSERT INTO mon_stats
           (pokemon_id,
            stat_id,
            base_stat,
            effort)
        VALUES (?, ?, ?, ?);
    ''', to_db)
    conn.commit()

    with open('pokemon_types.csv', 'r') as infile:
        reader = csv.DictReader(infile)
        to_db = [(row['pokemon_id'], row['type_id'], row['slot']) for row in reader]

    cursor.executemany('''
        INSERT INTO mon_types
           (pokemon_id,
            type_id,
            slot)
        VALUES (?, ?, ?);
    ''', to_db)
    conn.commit()


def types(conn, cursor):
    """
    Defines the types table and loads its data.
    """

    cursor.execute('''
        CREATE TABLE types 
           (id INT,
            identifier TEXT,
            damage_class_id INT);
    ''')
    cursor.execute('''
        CREATE TABLE type_efficacy
           (damage_type_id INT,
            target_type_id INT,
            damage_factor INT);
    ''')

    with open('types.csv', 'r') as infile:
        reader = csv.DictReader(infile)
        to_db = [(row['id'], row['identifier'], row['damage_class_id']) for row in reader]

    cursor.executemany('''
        INSERT INTO types
           (id,
            identifier,
            damage_class_id)
        VALUES (?, ?, ?);
    ''', to_db)
    conn.commit()

    with open('type_efficacy.csv', 'r') as infile:
        reader = csv.DictReader(infile)
        to_db = [(row['damage_type_id'], row['target_type_id'],
                  row['damage_factor']) for row in reader]

    cursor.executemany('''
        INSERT INTO type_efficacy
           (damage_type_id,
            target_type_id,
            damage_factor)
        VALUES (?, ?, ?);
    ''', to_db)
    conn.commit()


def stats(conn, cursor):
    """
    Defines the stats table and loads its data.
    """

    cursor.execute('''
        CREATE TABLE stats 
           (id INT,
            damage_class_id INT,
            identifier TEXT,
            is_battle_only INT);
    ''')

    with open('stats.csv', 'r') as infile:
        reader = csv.DictReader(infile)
        to_db = [(row['id'], row['damage_class_id'], row['identifier'],
                  row['is_battle_only']) for row in reader]

    cursor.executemany('''
        INSERT INTO stats
           (id,
            damage_class_id,
            identifier,
            is_battle_only)
        VALUES (?, ?, ?, ?);
    ''', to_db)
    conn.commit()


if __name__ == "__main__":
    sys.exit(main())
