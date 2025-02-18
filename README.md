# cmake-project-demo



# Prerequisite

```bash
# Install systemd library
sudo apt install libsystemd-dev
```


# Install the services


```bash
sudo make install
sudo systemctl daemon-reload
sudo systemctl enable my_test_systemd.service
```

# Start the services

```bash
sudo systemctl start my_test_systemd.service
```

# Check the status

```bash
systemctl status my_test_systemd.service
```

OR

```bash
journalctl --follow --unit=my_test_systemd.service
```
