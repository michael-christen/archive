import argparse
import sys
import time
import logging
import yaml

from watchdog.observers import Observer
from watchdog.events import PatternMatchingEventHandler

from project_ion.monitoring import FileMonitoringEventHandler


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--config', type=str, default='~/.projection/monitor_config.yml',
        help='Set location of config file. Defaults to '
             '"~/.projection/monitor_config.yml"')
    parser.add_argument(
        '--elastic_uri', type=str, default='http://localhost:9200',
        help='ElasticSearch URI, defaults to localhost:9200')
    args = parser.parse_args()

    logging.basicConfig(level=logging.INFO,
                        format='%(asctime)s - %(message)s',
                        datefmt='%Y-%m-%d %H:%M:%S')

    monitor_config = yaml.load(open(args.config, 'r').read())
    event_handler = FileMonitoringEventHandler(
        ignore_patterns=monitor_config['global_ignore'],
        ignore_directories=True)
    observers = []
    for path in monitor_config['monitor_paths']:
        observer = Observer()
        observer.schedule(event_handler, path, recursive=True)
        observer.start()
        observers.append(observer)
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        observer.stop()
    observer.join()

if __name__ == "__main__":
    main()
